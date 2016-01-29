#include "gwinabout.h"

#include <QLabel>
#include <QString>

#include <QVBoxLayout>
#include <QPushButton>

#include "log.h"

using namespace Util;

GWinAbout::GWinAbout(QWidget *parent) : QDialog(parent) {
    init_win();
}

void GWinAbout::init_win() {
    this->resize(400, 250);
    this->setFixedSize(this->size()); // TODO: what does this do on Windows?
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(5);
    this->setLayout(layout);

    QString about_text = "\
<h1 align=\"center\">About</h1>\
<p>This software was written for the <b>AQA Computing (2510)</b> A-level course.</p>\
<p>All source code for this software is available under the MIT license (see \
LICENSE). You can download the latest version of the source files at the <a \
href=\"https://github.com/raehik/digital-organiser\">digital-organiser GitHub page</a>.</p>\
<p>Please see the ATTRIBUTION.md file for attribution and credits.</p>\
";
    QLabel *about = new QLabel(about_text);
    // open HTML links in default browser
    about->setOpenExternalLinks(true);
    about->setWordWrap(true);
    layout->addWidget(about, 0, Qt::AlignTop);

    QPushButton *b_exit = new QPushButton(tr("Close"));
    layout->addWidget(b_exit);
    connect(b_exit, SIGNAL(clicked()), this, SLOT(close()));
}
