#ifndef CAPTURERECORDWINDOW_H
#define CAPTURERECORDWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>

class CaptureRecordWindow : public QWidget
{
	Q_OBJECT
public:
	explicit CaptureRecordWindow(QWidget *parent = nullptr);

signals:

public slots:
	void AddNewRow(const QString &SrcIp, const QString &DstIp, const QString &PkgSize,
				   const QString &Url, const QString &Time);

private:
	QVBoxLayout *Layout;
	QTableWidget *CaptureRecordTable;
};

#endif // CAPTURERECORDWINDOW_H