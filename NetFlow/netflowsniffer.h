#ifndef SNIFFER_H
#define SNIFFER_H

#include <unordered_set>
#include <unordered_map>
#include <chrono>
#include <QObject>
#include <QMetaType>
#include <QDateTime>
#include <tins/tins.h>
#include <tins/tcp_ip/stream_follower.h>
#include "startwindow.h"

using namespace Tins;
using namespace Tins::TCPIP;

class NetFlowSniffer : public QObject
{
    Q_OBJECT
public:
    explicit NetFlowSniffer(QObject *parent = nullptr);

	void SetUrlSet(const std::unordered_set<std::string>&);
	void SetFilterRule(const std::string&);

	using TimeType = decltype(std::chrono::system_clock::now());

signals:
	void UpdatePieChart(const std::unordered_map<std::string, int>&);
	void UpdateLineChart(const std::unordered_map<std::string, int>&);
	void InitializeAnalysisChart(const std::unordered_set<std::string>&);
	void NewUrlDetected(const QString &SrcIp, const QString &DstIp, const QString &PkgSize,
						const QString &Url, const QString &Time);

public slots:
	void BeginToSniff();

private:
	std::unordered_set<std::string> UrlSet;
	std::unordered_map<std::string, int> UrlCount, CountIn30Secs;
	std::unordered_map<std::string, TimeType> LastVisitTimeOf;
	std::string FilterRule;

	TimeType LastUpdateOfLineChart;

	SnifferConfiguration Config;
	Sniffer _Sniffer;
	StreamFollower Follower;

	const int MAX_PAYLOAD = 3 * 1024;
};

#endif // SNIFFER_H