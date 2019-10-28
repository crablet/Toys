#include "netflowsniffer.h"

#include <iostream>

NetFlowSniffer::NetFlowSniffer(QObject *parent) 
	: QObject(parent),
	_Sniffer(NetworkInterface::default_interface().name()),
	LastUpdateOfLineChart(std::chrono::system_clock::now())
{
	qRegisterMetaType<std::unordered_set<std::string>>("const std::unordered_set<std::string>&");
	qRegisterMetaType<std::string>("const std::string&");
	qRegisterMetaType<std::unordered_map<std::string, int>>("const std::unordered_map<std::string, int>&");
}

void NetFlowSniffer::SetUrlSet(const std::unordered_set<std::string> &Urls)
{
	UrlSet = Urls;

	const auto Now = std::chrono::system_clock::now();
	for (const auto &r : UrlSet)	// initialize the last time of url visited
	{
		LastVisitTimeOf[r] = Now;
	}

	emit InitializeAnalysisChart(UrlSet);
}

void NetFlowSniffer::SetFilterRule(const std::string &Rules)
{
	FilterRule = Rules;
	_Sniffer.set_filter(FilterRule);
}

void NetFlowSniffer::BeginToSniff()
{
	Follower.new_stream_callback([=](Stream &OuterStream)
	{
		OuterStream.client_data_callback([=](Stream &InnerStream)
		{
			if (InnerStream.client_payload().size() > MAX_PAYLOAD)
			{
				InnerStream.ignore_client_data();
			}
		});

		OuterStream.server_data_callback([=](Stream &InnerStream)
		{
			auto ClientPayload = InnerStream.client_payload();
			auto ClientPayloadStr = std::string(ClientPayload.begin(), ClientPayload.end());

			bool CanUpdatePieChart = false, CanUpdateLineChart = false;

			using namespace std::chrono_literals;	// for the use of operator""s
			const auto Now = std::chrono::system_clock::now();
			if (Now - LastUpdateOfLineChart >= 3s)	// update LineChart every 3s
			{
				CanUpdateLineChart = true;

				LastUpdateOfLineChart = Now;
			}

			for (const auto &Url : UrlSet)
			{
				if (ClientPayloadStr.find(Url) != std::string::npos)
				{
					if (Now - LastVisitTimeOf[Url] >= 1s)
					{
						LastVisitTimeOf[Url] = Now;
						++UrlCount[Url];
						++CountIn30Secs[Url];

						CanUpdatePieChart = true;

						auto SrcIp = QString::fromStdString(InnerStream.server_addr_v4().to_string());
						auto DstIp = QString::fromStdString(InnerStream.client_addr_v4().to_string());
						auto UrlName = QString::fromStdString(Url);
						auto PkgSize = QString::number(ClientPayload.size());
						auto DateTime = QDateTime::currentDateTime().toString();
						emit NewUrlDetected(SrcIp, DstIp, PkgSize, UrlName, DateTime);
					}
				}
			}

			// fake code begin
			const std::string QQ = "QQ Client";
			if (UrlSet.find(QQ) != UrlSet.end() && ClientPayloadStr.find("1063221915") != std::string::npos)
			{
				if (Now - LastVisitTimeOf[QQ] >= 1s)
				{
					LastVisitTimeOf[QQ] = Now;
					++UrlCount[QQ];
					++CountIn30Secs[QQ];

					CanUpdatePieChart = true;
				}
			}
			// fake code end

			if (CanUpdatePieChart)
			{
				emit UpdatePieChart(UrlCount);
			}
			if (CanUpdateLineChart)
			{
				emit UpdateLineChart(CountIn30Secs);
				for (auto &r : CountIn30Secs)	// reset count to zero
				{
					r.second = 0;
				}
			}

			InnerStream.ignore_client_data();
			InnerStream.ignore_server_data();
		});

		OuterStream.auto_cleanup_payloads(false);
	});

	_Sniffer.sniff_loop([&](PDU &p)
	{
		Follower.process_packet(p);

		return true;
	});
}
