#include "capturerecordwindow.h"

CaptureRecordWindow::CaptureRecordWindow(QWidget *parent) : QWidget(parent)
{
	CaptureRecordTable = new QTableWidget(this);
	CaptureRecordTable->setColumnCount(5);
	CaptureRecordTable->setHorizontalHeaderLabels(QStringList({ "SrcIp", "DstIp", "PkgSize", "Url", "Time" }));
	CaptureRecordTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	CaptureRecordTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	CaptureRecordTable->setFocusPolicy(Qt::NoFocus);

	Layout = new QVBoxLayout(this);
	Layout->addWidget(CaptureRecordTable);
}

void CaptureRecordWindow::AddNewRow(const QString &SrcIp, const QString &DstIp, const QString &PkgSize,
									const QString &Url, const QString &Time)
{
	int NowRowCount = CaptureRecordTable->rowCount();
	CaptureRecordTable->insertRow(NowRowCount);

	auto *SrcIpItem = new QTableWidgetItem(SrcIp);
	auto *DstIpItem = new QTableWidgetItem(DstIp);
	auto *PkgSizeItem = new QTableWidgetItem(PkgSize);
	auto *UrlItem = new QTableWidgetItem(Url);
	auto *TimeItem = new QTableWidgetItem(Time);
	CaptureRecordTable->setItem(NowRowCount, 0, SrcIpItem);
	CaptureRecordTable->setItem(NowRowCount, 1, DstIpItem);
	CaptureRecordTable->setItem(NowRowCount, 2, PkgSizeItem);
	CaptureRecordTable->setItem(NowRowCount, 3, UrlItem);
	CaptureRecordTable->setItem(NowRowCount, 4, TimeItem);
}
