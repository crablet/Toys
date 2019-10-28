#include "netflow.h"

NetFlow::NetFlow(QWidget *parent)
    : QWidget(parent)
{
	setFixedSize(800, 555);
	setWindowIcon(QIcon(":/NetFlowIconSmall.jpg"));

	_StartWindow = new StartWindow;
	_AnalysisWindow = new AnalysisWindow;
	_CaptureRecordWindow = new CaptureRecordWindow;

	WindowContainer = new QStackedWidget;
	WindowContainer->addWidget(_StartWindow);
	WindowContainer->addWidget(_AnalysisWindow);
	WindowContainer->addWidget(_CaptureRecordWindow);

	_TopBarWidget = new TopBarWidget;
	connect(_TopBarWidget, &TopBarWidget::ShowStartWindow, [this]()
	{
		WindowContainer->setCurrentWidget(_StartWindow);
	});
	connect(_TopBarWidget, &TopBarWidget::ShowAnalysisWindow, [this]()
	{
		WindowContainer->setCurrentWidget(_AnalysisWindow);
	});
	connect(_TopBarWidget, &TopBarWidget::ShowCaptureRecordWindow, [this]()
	{
		WindowContainer->setCurrentWidget(_CaptureRecordWindow);
	});

	// set the background white
	QPalette BackgroundPalette(palette());
	BackgroundPalette.setColor(QPalette::Background, Qt::white);
	setPalette(BackgroundPalette);
	setAutoFillBackground(true);

	Layout = new QVBoxLayout(this);
	Layout->addWidget(_TopBarWidget);
	Layout->addWidget(WindowContainer);

	setLayout(Layout);

	InitialiazeConnect();
}

NetFlow::~NetFlow()
{

}

void NetFlow::InitialiazeUi()
{
}

void NetFlow::InitialiazeConnect()
{
	connect(_StartWindow, &StartWindow::OnSumitClicked, this, &NetFlow::BeginToSniffCaller);
	connect(this, &NetFlow::BeginToSniffSignal, this, &NetFlow::BeginToSniff);

	connect(&_Sniffer, &NetFlowSniffer::InitializeAnalysisChart, _AnalysisWindow, &AnalysisWindow::InitializeAnalysisChart);
	connect(&_Sniffer, &NetFlowSniffer::UpdatePieChart, _AnalysisWindow, &AnalysisWindow::UpdatePieChart);
	connect(&_Sniffer, &NetFlowSniffer::UpdateLineChart, _AnalysisWindow, &AnalysisWindow::UpdateLineChart);

	connect(&_Sniffer, &NetFlowSniffer::NewUrlDetected, _CaptureRecordWindow, &CaptureRecordWindow::AddNewRow);
}

void NetFlow::BeginToSniff()
{
	_Sniffer.moveToThread(&SnifferThread);
	connect(this, &NetFlow::BeginToSniffSignal, &_Sniffer, &NetFlowSniffer::BeginToSniff);
	SnifferThread.start();
}

void NetFlow::BeginToSniffCaller(const std::unordered_set<std::string> &UrlSet,
							     const std::string &FilterRule)
{
	_Sniffer.SetFilterRule(FilterRule);
	_Sniffer.SetUrlSet(UrlSet);
	BeginToSniff();

	emit BeginToSniffSignal();
}

