#ifndef NETFLOW_H
#define NETFLOW_H

#include <unordered_set>
#include <QThread>
#include <QString>
#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QStackedWidget>
#include "topbarwidget.h"
#include "startwindow.h"
#include "analysiswindow.h"
#include "capturerecordwindow.h"
#include "netflowsniffer.h"

class NetFlow : public QWidget
{
    Q_OBJECT

public:
    NetFlow(QWidget *parent = 0);
    ~NetFlow();

signals:
	void BeginToSniffSignal();

private slots:
	void BeginToSniffCaller(const std::unordered_set<std::string>&,
							const std::string&);

private:
	void InitialiazeUi();
	void InitialiazeConnect();
	void BeginToSniff();

private:
	QVBoxLayout *Layout;
	QStackedWidget *WindowContainer;

	TopBarWidget *_TopBarWidget;
	StartWindow *_StartWindow;
	AnalysisWindow *_AnalysisWindow;
	CaptureRecordWindow *_CaptureRecordWindow;

	std::unordered_set<std::string> WebSet;

	NetFlowSniffer _Sniffer;
	QThread SnifferThread;
};

#endif // NETFLOW_H
