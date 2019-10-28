#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <unordered_set>
#include <string>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QSizePolicy>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>

class StartWindow : public QWidget
{
	Q_OBJECT
public:
	explicit StartWindow(QWidget *parent = nullptr);

signals:
	void OnSumitClicked(const std::unordered_set<std::string>&,
						const std::string&);

public slots:

private:
	std::unordered_set<std::string> Urls;
	std::string FilterRule;
};

#endif // STARTWINDOW_H