#include "startwindow.h"

StartWindow::StartWindow(QWidget *parent) : QWidget(parent)
{
	auto *InputForm = new QFormLayout(this);
	InputForm->setRowWrapPolicy(QFormLayout::WrapAllRows);

	auto *TargetWebEdit = new QTextEdit;
	InputForm->addRow("Target Web", TargetWebEdit);

	auto *FilterEdit = new QLineEdit;
	InputForm->addRow("Filter", FilterEdit);

	auto *SubmitBtn = new QPushButton("Submit");
	InputForm->addRow(SubmitBtn);
	connect(SubmitBtn, &QPushButton::clicked, this, [this, TargetWebEdit, FilterEdit, SubmitBtn]()
	{
		SubmitBtn->setText("Submited successfully!");
		SubmitBtn->setDisabled(true);

		// for example: jd.com
		auto AllWebLine = TargetWebEdit->toPlainText().split("\n", QString::SkipEmptyParts);
		for (const auto &r : AllWebLine)
		{
			Urls.insert(r.toStdString());
		}

		// for example: tcp port 443 or tcp port 80 or udp 8000
		FilterRule = FilterEdit->text().toStdString();

		// fake code begin
		if (FilterRule.find("udp port 8000") != std::string::npos)	// for QQ detect
		{
			Urls.insert("QQ Client");
		}
		// fake code end

		emit OnSumitClicked(Urls, FilterRule);
	});

	setLayout(InputForm);
}
