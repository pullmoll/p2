/****************************************************************************
 *
 * P2 emulator main window
 *
 * Copyright (C) 2019 Jürgen Buchmüller <pullmoll@t-online.de>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************/
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QStandardPaths>
#include <QTextStream>
#include <QTimer>
#include <QSettings>
#include <QLabel>
#include <QFontDatabase>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"
#include "p2doc.h"
#include "gotoaddress.h"
#include "gotoline.h"
#include "palettesetup.h"
#include "textbrowser.h"
#include "p2hub.h"
#include "p2cog.h"
#include "p2asm.h"
#include "p2asmmodel.h"
#include "p2dasm.h"
#include "p2dasmmodel.h"
#include "p2symboltable.h"
#include "p2symbolsmodel.h"
#include "p2opcodedelegate.h"
#include "p2sourcedelegate.h"
#include "p2referencesdelegate.h"
#include "p2symbolsorter.h"

static const int ncogs = 8;
static const QLatin1String key_windowGeometry("windowGeometry");
static const QLatin1String key_windowState("windowState");
static const QLatin1String grp_assembler("assembler");
static const QLatin1String grp_disassembler("disassembler");
static const QLatin1String grp_palette("palette");
static const QLatin1String key_opcodes("opcodes");
static const QLatin1String key_lowercase("lowercase");
static const QLatin1String key_current_row("current_row");
static const QLatin1String key_current_column("current_column");
static const QLatin1String key_column_address("hide_address");
static const QLatin1String key_column_origin("hide_origin");
static const QLatin1String key_column_tokens("hide_tokens");
static const QLatin1String key_column_opcode("hide_opcode");
static const QLatin1String key_column_errors("hide_errors");
static const QLatin1String key_column_symbols("hide_symbols");
static const QLatin1String key_column_instruction("hide_instruction");
static const QLatin1String key_column_source("hide_source");
static const QLatin1String key_column_description("hide_description");
static const QLatin1String key_font_size("font_size");
static const QLatin1String key_splitter_source_percent("source_percent");
static const QLatin1String key_splitter_symbols_percent("symbols_percent");
static const QLatin1String key_splitter_errors_percent("errors_percent");

static const QLatin1String key_source("source");
static const QLatin1String key_directory("directory");
static const QLatin1String key_filename("filename");
static const QLatin1String key_history("directory");

static const QLatin1String key_lines("lines");
static const QLatin1String key_status("status");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_vcog()
    , m_hub(new P2Hub(ncogs, this))
    , m_asm(new P2Asm(this))
    , m_amodel(new P2AsmModel(m_asm))
    , m_dasm(new P2Dasm(m_hub->cog(0)))
    , m_dmodel(new P2DasmModel(m_dasm))
    , m_smodel(new P2SymbolsModel())
    , m_font(QLatin1String("Source Code Pro"), 9)
    , m_asm_font_size(11)
    , m_dasm_font_size(11)
    , m_source_percent(80)
    , m_symbols_percent(15)
    , m_errors_percent(5)
{
    qsrand(static_cast<uint>(QDateTime::currentMSecsSinceEpoch()));
    ui->setupUi(this);

    setWindowTitle(QString("%1 v%2").arg(qApp->applicationName()).arg(qApp->applicationVersion()));
    setupMenu();
    setupTabWidget();
    setupToolbars();
    setupStatusbar();

    setupAssembler();
    setupDisassembler();
    setupCogView();

    restoreSettings();
    setupFonts();

    // loadSource(QStringLiteral(":/spin2/spin2_interpreter.spin2"));
    // loadSource(QStringLiteral(":/spin2/pointers.spin2"));
    // loadSource(QStringLiteral(":/spin2/USBHost.spin2"));
    // loadSource(QStringLiteral(":/spin2/VGA_640_x_480_8bpp.spin2"));
    // loadSource(QStringLiteral(":/spin2/P2-qz80-rr032.spin2"));
    // loadSource(QStringLiteral(":/spin2/ROM_Booter_v33_01j.spin2"));
    loadObjectRandom();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::saveSettings()

{
    QSettings s;
    s.setValue(key_windowGeometry, saveGeometry());
    s.setValue(key_windowState, saveState());
    saveSettingsAsm();
    saveSettingsDasm();
    saveSettingsPalette();

}

void MainWindow::restoreSettings()
{
    QSettings s;
    restoreGeometry(s.value(key_windowGeometry).toByteArray());
    restoreState(s.value(key_windowState).toByteArray());
    restoreSettingsAsm();
    restoreSettingsDasm();
    restoreSettingsPalette();
}

void MainWindow::saveSettingsAsm()
{
    QSettings s;
    QList<int> sizes = ui->splSource->sizes();
    QSize size = ui->tabAsm->size();
    if (size.height() > 0) {
        m_source_percent = sizes.value(0) * 100 / size.height();
        m_symbols_percent = sizes.value(1) * 100 / size.height();
        m_errors_percent = sizes.value(2) * 100 / size.height();
    }

    s.beginGroup(grp_assembler);
    s.setValue(key_opcodes, m_amodel->opcode_format());
    s.setValue(key_column_origin, ui->tvAsm->isColumnHidden(P2AsmModel::c_Origin));
    s.setValue(key_column_address, ui->tvAsm->isColumnHidden(P2AsmModel::c_Address));
    s.setValue(key_column_opcode, ui->tvAsm->isColumnHidden(P2AsmModel::c_Opcode));
    s.setValue(key_column_tokens, ui->tvAsm->isColumnHidden(P2AsmModel::c_Tokens));
    s.setValue(key_column_symbols, ui->tvAsm->isColumnHidden(P2AsmModel::c_Symbols));
    s.setValue(key_column_errors, ui->tvAsm->isColumnHidden(P2AsmModel::c_Errors));
    s.setValue(key_column_source, ui->tvAsm->isColumnHidden(P2AsmModel::c_Source));
    QModelIndex index = ui->tvAsm->currentIndex();
    s.setValue(key_current_row, index.row());
    s.setValue(key_current_column, index.column());
    s.setValue(key_font_size, ui->tvAsm->font().pointSize());
    s.setValue(key_splitter_source_percent, m_source_percent);
    s.setValue(key_splitter_symbols_percent, m_symbols_percent);
    s.setValue(key_splitter_errors_percent, m_errors_percent);

    s.endGroup();
}

void MainWindow::restoreSettingsAsm()
{
    QSettings s;
    s.beginGroup(grp_assembler);
    setAsmOpcodes(s.value(key_opcodes, fmt_bin).toInt());
    int row = s.value(key_current_row).toInt();
    int column = s.value(key_current_row).toInt();
    ui->tvAsm->setCurrentIndex(m_amodel->index(row, column));
    ui->tvAsm->setColumnHidden(P2AsmModel::c_Origin, s.value(key_column_origin, false).toBool());
    ui->tvAsm->setColumnHidden(P2AsmModel::c_Address, s.value(key_column_address, false).toBool());
    ui->tvAsm->setColumnHidden(P2AsmModel::c_Opcode, s.value(key_column_opcode, false).toBool());
    ui->tvAsm->setColumnHidden(P2AsmModel::c_Tokens, s.value(key_column_tokens, false).toBool());
    ui->tvAsm->setColumnHidden(P2AsmModel::c_Symbols, s.value(key_column_symbols, false).toBool());
    ui->tvAsm->setColumnHidden(P2AsmModel::c_Errors, s.value(key_column_errors, false).toBool());
    ui->tvAsm->setColumnHidden(P2AsmModel::c_Source, s.value(key_column_source, false).toBool());
    m_asm_font_size = s.value(key_font_size, 11).toInt();
    m_source_percent = qBound(1,s.value(key_splitter_source_percent, m_source_percent).toInt(),100);
    m_symbols_percent = qBound(1,s.value(key_splitter_symbols_percent, m_symbols_percent).toInt(),100);
    m_errors_percent = qBound(1,s.value(key_splitter_errors_percent, m_errors_percent).toInt(),100);
    s.endGroup();
    setAsmFontSize(m_asm_font_size);
    resizeSourceSplitter();
}

void MainWindow::saveSettingsDasm()
{
    QSettings s;
    s.beginGroup(grp_disassembler);
    s.setValue(key_opcodes, m_dmodel->opcode_format());
    s.setValue(key_lowercase, ui->action_Dasm_Lowercase->isChecked());
    s.setValue(key_column_address, ui->tvDasm->isColumnHidden(P2DasmModel::c_Address));
    s.setValue(key_column_opcode, ui->tvDasm->isColumnHidden(P2DasmModel::c_Opcode));
    s.setValue(key_column_instruction, ui->tvDasm->isColumnHidden(P2DasmModel::c_Instruction));
    s.setValue(key_column_description, ui->tvDasm->isColumnHidden(P2DasmModel::c_Description));
    QModelIndex index = ui->tvDasm->currentIndex();
    s.setValue(key_current_row, index.row());
    s.setValue(key_current_column, index.column());
    s.setValue(key_font_size, ui->tvDasm->font().pointSize());
    s.endGroup();
}

void MainWindow::restoreSettingsDasm()
{
    QSettings s;
    s.beginGroup(grp_disassembler);
    setDasmOpcodes(s.value(key_opcodes, fmt_bin).toInt());
    setDasmLowercase(s.value(key_lowercase).toBool());
    ui->tvDasm->selectRow(s.value(key_current_row).toInt());
    ui->tvDasm->setColumnHidden(P2DasmModel::c_Address, s.value(key_column_address, false).toBool());
    ui->tvDasm->setColumnHidden(P2DasmModel::c_Opcode, s.value(key_column_opcode, false).toBool());
    ui->tvDasm->setColumnHidden(P2DasmModel::c_Instruction, s.value(key_column_instruction, false).toBool());
    ui->tvDasm->setColumnHidden(P2DasmModel::c_Description, s.value(key_column_description, false).toBool());
    m_dasm_font_size = s.value(key_font_size, 11).toInt();
    s.endGroup();
    setDasmFontSize(m_dasm_font_size);
}

void MainWindow::saveSettingsPalette()
{
    QSettings s;
    s.beginGroup(grp_palette);
    s.remove(QStringLiteral(""));
    QHash<P2Colors::p2_palette_e,QColor> hash = Colors.hash();
    foreach (P2Colors::p2_palette_e pal, hash.keys()) {
        QString key = Colors.palette_name(pal);
        QColor color = Colors.palette_color(pal);
        QString name = Colors.closest(color);
        s.setValue(key, name);
    }
    s.endGroup();
}

void MainWindow::restoreSettingsPalette()
{
    QSettings s;
    s.beginGroup(grp_palette);
    foreach(const QString& key, s.allKeys()) {
        P2Colors::p2_palette_e pal = Colors.palette_key(key);
        QString name = s.value(key).toString();
        Colors.set_palette_color(pal, name);
    }
}

void MainWindow::about()
{
    About dlg;
    dlg.setApplicationName(qApp->applicationName());
    dlg.setApplicationVersion(qApp->applicationVersion());
    dlg.adjustSize();
    dlg.exec();
}

void MainWindow::aboutQt5()
{
    qApp->aboutQt();
}

void MainWindow::help_opcodes()
{
    QStringList html = Doc.html_opcodes();
    TextBrowser dlg;
    dlg.set_title(tr("Propeller2 Opcode Table"));
    dlg.set_html(html);
    dlg.exec();
}

void MainWindow::goto_hex(const QString& address)
{
    bool ok;
    p2_LONG addr = address.toUInt(&ok, 16);
    if (ok)
        ui->tvDasm->selectRow(static_cast<int>(addr / 4));
}

void MainWindow::goto_cog()
{
    goto_hex("00000");
}

void MainWindow::goto_lut()
{
    goto_hex("00800");
}

void MainWindow::goto_rom()
{
    goto_hex("fc000");
}

void MainWindow::goto_address()
{
    GotoAddress dlg;
    if (QDialog::Accepted == dlg.exec()) {
        goto_hex(dlg.address());
    }
}

void MainWindow::setAsmOpcodes(int mode)
{
    p2_FORMAT_e format = static_cast<p2_FORMAT_e>(mode);
    ui->action_Asm_Opcodes_bin->setChecked(format == fmt_bin);
    ui->action_Asm_Opcodes_byt->setChecked(format == fmt_bit);
    ui->action_Asm_Opcodes_dec->setChecked(format == fmt_dec);
    ui->action_Asm_Opcodes_hex->setChecked(format == fmt_hex);
    m_amodel->setOpcodeFormat(format);
    updateAsmColumnSizes();
}

void MainWindow::setAsmOpcodes()
{
    QAction* act = qobject_cast<QAction*>(sender());
    Q_ASSERT(act);
    setAsmOpcodes(act->data().toInt());
}

void MainWindow::incAsmFontSize()
{
    QFont font = ui->tvAsm->font();
    int size = font.pointSize();
    if (size < 24) {
        size++;
        setAsmFontSize(size);
    }
}

void MainWindow::decAsmFontSize()
{
    QFont font = ui->tvAsm->font();
    int size = font.pointSize();
    if (size > 5) {
        size--;
        setAsmFontSize(size);
    }
}

void MainWindow::setAsmFontSize(int size)
{
    ui->tvAsm->setUpdatesEnabled(false);
    ui->tvSymbols->setUpdatesEnabled(false);

    QFont font = ui->tvAsm->font();
    font.setPointSize(size);
    ui->tvAsm->setFont(font);
    m_amodel->setFont(font);

    ui->tvSymbols->setFont(font);
    m_smodel->setFont(font);

    updateAsmColumnSizes();
    updateSymbolsColumnSizes();

    ui->tvSymbols->setUpdatesEnabled(true);
    ui->tvAsm->setUpdatesEnabled(true);
}

void MainWindow::setDasmOpcodes(int mode)
{
    p2_FORMAT_e format = static_cast<p2_FORMAT_e>(mode);
    ui->action_Dasm_Opcodes_bin->setChecked(format == fmt_bin);
    ui->action_Dasm_Opcodes_byt->setChecked(format == fmt_bit);
    ui->action_Dasm_Opcodes_dec->setChecked(format == fmt_dec);
    ui->action_Dasm_Opcodes_hex->setChecked(format == fmt_hex);
    m_dmodel->setOpcodeFormat(format);
    updateDasmColumnSizes();
}

void MainWindow::setDasmOpcodes()
{
    QAction* act = qobject_cast<QAction*>(sender());
    Q_ASSERT(act);
    setDasmOpcodes(act->data().toInt());
}

void MainWindow::incDasmFontSize()
{
    QFont font = ui->tvDasm->font();
    int size = font.pointSize();
    if (size < 24) {
        size++;
        setDasmFontSize(size);
    }
}

void MainWindow::decDasmFontSize()
{
    QFont font = ui->tvDasm->font();
    int size = font.pointSize();
    if (size > 5) {
        size--;
        setDasmFontSize(size);
    }
}

void MainWindow::setDasmFontSize(int size)
{
    ui->tvDasm->setUpdatesEnabled(false);

    QFont font = ui->tvDasm->font();
    font.setPointSize(size);
    ui->tvDasm->setFont(font);
    m_dmodel->setFont(font);
    updateDasmColumnSizes();

    ui->tvDasm->setUpdatesEnabled(true);
}

void MainWindow::setAsmHeaderColums(const QPoint& pos)
{
    QList<P2AsmModel::column_e> columns = m_amodel->columns();

    QMenu m(tr("Select columns"));
    foreach(P2AsmModel::column_e column, columns) {
        QAction* act = new QAction(m_amodel->headerData(column, Qt::Horizontal).toString());
        act->setData(column);
        act->setCheckable(true);
        act->setChecked(!ui->tvAsm->isColumnHidden(column));
        m.addAction(act);
    }

    // Popup menu
    QHeaderView* hv = ui->tvAsm->horizontalHeader();
    QAction* act = m.exec(hv->mapToGlobal(pos));
    if (!act)
        return;
    // hide or show the selected column
    P2AsmModel::column_e column = static_cast<P2AsmModel::column_e>(act->data().toInt());
    ui->tvAsm->setColumnHidden(column, !act->isChecked());
}

void MainWindow::setDasmHeaderColums(const QPoint& pos)
{
    QList<P2DasmModel::column_e> columns = m_dmodel->columns();

    QMenu m(tr("Select columns"));
    foreach(P2DasmModel::column_e column, columns) {
        QAction* act = new QAction(m_dmodel->headerData(column, Qt::Horizontal).toString());
        act->setData(column);
        act->setCheckable(true);
        act->setChecked(!ui->tvDasm->isColumnHidden(column));
        m.addAction(act);
    }

    // Popup menu
    QHeaderView* hv = ui->tvDasm->horizontalHeader();
    QAction* act = m.exec(hv->mapToGlobal(pos));
    if (!act)
        return;
    // hide or show the selected column
    P2DasmModel::column_e column = static_cast<P2DasmModel::column_e>(act->data().toInt());
    ui->tvDasm->setColumnHidden(column, !act->isChecked());
}

void MainWindow::setSymbolsHeaderColums(const QPoint& pos)
{
    QList<P2SymbolsModel::column_e> columns = m_smodel->columns();

    QMenu m(tr("Select columns"));
    foreach(P2SymbolsModel::column_e column, columns) {
        QAction* act = new QAction(m_smodel->headerData(column, Qt::Horizontal).toString());
        act->setData(column);
        act->setCheckable(true);
        act->setChecked(!ui->tvSymbols->isColumnHidden(column));
        m.addAction(act);
    }

    // Popup menu
    QHeaderView* hv = ui->tvSymbols->horizontalHeader();
    QAction* act = m.exec(hv->mapToGlobal(pos));
    if (!act)
        return;
    // hide or show the selected column
    P2SymbolsModel::column_e column = static_cast<P2SymbolsModel::column_e>(act->data().toInt());
    ui->tvSymbols->setColumnHidden(column, !act->isChecked());
}

void MainWindow::hubSingleStep()
{
    m_hub->execute(ncogs*2);
    for (int id = 0; id < ncogs; id++)
        m_vcog[id]->updateView();
}

void MainWindow::loadObject(const QString& filename)
{
    QFileInfo info(filename);
    ui->tabWidget->setTabText(1, QString("%1 [%2]").arg(tr("Disassembler")).arg(info.fileName()));

    if (!info.path().startsWith(QChar(':')))
        m_hub->set_pathname(info.path());
    m_hub->load_obj(filename);
    m_dmodel->invalidate();
    updateDasmColumnSizes();
    ui->tvDasm->update();
}

void MainWindow::loadObjectRandom()
{
    QDir dir(QStringLiteral(":/bin"));
    QStringList name_filters =
            QStringList()
            << QStringLiteral("*.bin")
            << QStringLiteral("*.obj");
    QDir::Filters filters = QDir::Files;
    QDir::SortFlags sort = QDir::Name;
    QStringList files = dir.entryList(name_filters, filters, sort);
    QString objectfile = QString("%1/%2")
                         .arg(dir.path())
                         .arg(files[qrand() % files.count()]);
    loadObject(objectfile);
}

void MainWindow::openSource(const QString& sourcefile)
{
    QSettings s;
    s.beginGroup(key_source);
    QString directory = s.value(key_directory).toString();
    QString filename = s.value(key_filename).toString();
    QStringList history = s.value(key_history).toStringList();
    s.endGroup();

    if (sourcefile.isEmpty()) {
        QFileDialog dlg(this);

        dlg.setAcceptMode(QFileDialog::AcceptOpen);
        dlg.setDefaultSuffix(QStringLiteral("spin2"));
        dlg.setDirectory(directory);
        dlg.setFilter(QDir::AllEntries | QDir::Readable);
        dlg.setHistory(history);
        dlg.setNameFilter(tr("Spin2 source files (*.spin2)"));
        QString propeller2_path = QString("%1/Propeller2").arg(QDir::homePath());
        QString appdata_path = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).first();
        QList<QUrl> urls = QList<QUrl>()
            << QUrl::fromLocalFile(propeller2_path)
            << QUrl::fromLocalFile(appdata_path);

        if (QDialog::Accepted != dlg.exec())
            return;
        QStringList selected = dlg.selectedFiles();
        if (selected.isEmpty())
            return;

        directory = dlg.directory().path();
        filename = selected.first();
        filename.remove(QDir::cleanPath(directory) + QStringLiteral("/"));
        history = dlg.history();
        s.beginGroup(key_source);
        s.setValue(key_directory, directory);
        s.setValue(key_filename, filename);
        s.setValue(key_history, history);
        s.endGroup();

        filename = QString("%1/%2")
                   .arg(directory)
                   .arg(filename);
    } else {
        filename = sourcefile;
    }

    loadSource(filename);
}

void MainWindow::loadSource(const QString& filename)
{
    QFileInfo info(filename);
    ui->tabWidget->setTabText(0, QString("%1 [%2]").arg(tr("Assembler")).arg(info.fileName()));

    if (!info.path().startsWith(QChar(':')))
        m_asm->set_pathname(info.path());
    m_asm->load(filename);
    m_amodel->invalidate();
    updateAsmColumnSizes();
    updateSymbolsColumnSizes();
    ui->tvAsm->setCurrentIndex(m_amodel->index(0, P2AsmModel::c_Source));
    ui->tvAsm->update();

    QLabel* lbl_lines = ui->toolbarAsm->findChild<QLabel*>(key_lines);
    if (lbl_lines)
        lbl_lines->setText(tr("%1 lines").arg(m_asm->count()));
    assemble();
}

void MainWindow::loadSourceRandom()
{
    QDir dir(QStringLiteral(":/spin2"));
    QStringList name_filters = QStringList() << QStringLiteral("*.spin2");
    QDir::Filters filters = QDir::Files;
    QDir::SortFlags sort = QDir::Name;
    QStringList files = dir.entryList(name_filters, filters, sort);
    QString sourcecode = QString("%1/%2")
                         .arg(dir.path())
                         .arg(files[qrand() % files.count()]);
    loadSource(sourcecode);
}

void MainWindow::assemble()
{
    QStringList source = m_asm->source();
    ui->tbErrors->clear();
    ui->splSource->widget(2)->setVisible(false);
    m_num_errors = 0;

    qint64 t0 = QDateTime::currentMSecsSinceEpoch();
    if (m_asm->assemble(source)) {
        qint64 t1 = QDateTime::currentMSecsSinceEpoch();
        QLabel* status = ui->statusBar->findChild<QLabel*>(key_status);
        if (status)
            status->setText(tr("Assembly took %1 ms.").arg(t1 - t0));

        // Inspect result
        const QModelIndex idx = ui->tvAsm->currentIndex();

        m_amodel->invalidate();
        ui->tvAsm->resizeRowsToContents();
        ui->tvAsm->setCurrentIndex(idx);
        m_smodel->setTable(m_asm->symbols());
    }
}

void MainWindow::palette_setup()
{
    QLayout* layout = ui->verticalLayout_2;
    PaletteSetup* dlg = layout->findChild<PaletteSetup *>(QStringLiteral("PaletteSetup"));
    if (dlg) {
        layout->removeWidget(dlg);
    } else {
        dlg = new PaletteSetup(this);
        layout->addWidget(dlg);
        connect(dlg, SIGNAL(changedPalette()), m_amodel, SLOT(invalidate()));
    }
}

void MainWindow::print_error(int pass, int line, const QString& message)
{
    QString str_pass = QString("%1 #%2 - ")
                       .arg(tr("Pass"))
                       .arg(QString::number(pass));
    QString str_line = QString("%1 <a href=\"%2#%3\">#%3</a>: ")
                       .arg(tr("Line"))
                        .arg(key_tv_asm)
                       .arg(QString::number(line));
    QString error = str_pass + str_line + message;
    ui->tbErrors->append(error);
    m_num_errors++;
    ui->splSource->widget(2)->setVisible(true);
}

void MainWindow::goto_line(const QUrl& url)
{
    const P2SymbolTable& table = m_asm->symbols();
    const QString& path = url.path();
    const QString& name = url.query();
    const QStringList& frag = url.fragment().split(QChar(','));
    const int lineno = frag.value(0).toInt();
    const int pos = frag.value(1).toInt();
    const int len = frag.value(2).toInt();

    const P2Symbol symbol = table->symbol(name);
    const P2Words& words = m_asm->words(lineno);
    P2Word word;
    for (int i = 0; !word.isValid() && i < words.count(); i++)
        if (pos == words[i].pos() && len == words[i].len())
            word = words[i];

    if (path == key_tv_asm) {
        const QModelIndex idx = m_amodel->index(lineno - 1, P2AsmModel::c_Source);
        m_amodel->set_highlight(idx, symbol, word);
        ui->tvAsm->setCurrentIndex(idx);
        ui->tvAsm->viewport()->repaint();
        // ui->tvAsm->setFocus(Qt::OtherFocusReason);
    }
}

void MainWindow::goto_line_number()
{
    GotoLine dlg(this);
    if (QDialog::Accepted != dlg.exec())
        return;
    QUrl url(key_tv_asm);
    url.setFragment(QString::number(dlg.number()));
    goto_line(url);
}

void MainWindow::resizeSourceSplitter()
{
    while (m_source_percent + m_symbols_percent + m_errors_percent > 100) {
        if (m_errors_percent > m_symbols_percent) {
            m_errors_percent--;
        } else {
            m_symbols_percent--;
        }
    }
    QList<int> resized = {m_source_percent, m_symbols_percent, m_errors_percent};
    const QList<int> sizes = ui->splSource->sizes();
    const int height = ui->tabAsm->height();
    for (int i = 0; i < resized.count(); i++)
        resized[i] = height * resized[i] / 100;
    ui->splSource->setSizes(resized);
    ui->splSource->widget(2)->setVisible(m_num_errors > 0);
}

void MainWindow::setDasmLowercase(bool check)
{
    ui->action_Dasm_Lowercase->setChecked(check);
    m_dasm->set_lowercase(check);
    p2_LONG PC = m_hub->cog(0)->rd_PC();
    int row = static_cast<int>((PC < HUB_ADDR0) ? PC : PC / 4);
    m_dmodel->invalidate();
    ui->tvDasm->selectRow(row);
}

void MainWindow::setupAssembler()
{
    connect(m_asm, SIGNAL(Error(int,int,QString)), SLOT(print_error(int,int,QString)));

    // prevent opening of (external) links
    ui->tbErrors->setOpenLinks(false);
    ui->tbErrors->setOpenExternalLinks(false);
    ui->splSource->setCollapsible(1, false);
    ui->splSource->setCollapsible(2, true);

    // but connect to the anchorClicked(QUrl) signal
    connect(ui->tbErrors, SIGNAL(anchorClicked(QUrl)), SLOT(goto_line(QUrl)), Qt::UniqueConnection);

    ui->tvAsm->setFocusPolicy(Qt::ClickFocus);
    ui->tvAsm->setEditTriggers(QAbstractItemView::DoubleClicked
                               | QAbstractItemView::SelectedClicked
                               | QAbstractItemView::EditKeyPressed
                               | QAbstractItemView::AnyKeyPressed);
    ui->tvAsm->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tvAsm->setSelectionBehavior(QAbstractItemView::SelectItems);

    QAbstractItemDelegate* od = ui->tvAsm->itemDelegateForColumn(P2AsmModel::c_Opcode);
    ui->tvAsm->setItemDelegateForColumn(P2AsmModel::c_Opcode, new P2OpcodeDelegate);
    delete od;

    QAbstractItemDelegate* sd = ui->tvAsm->itemDelegateForColumn(P2AsmModel::c_Source);
    ui->tvAsm->setItemDelegateForColumn(P2AsmModel::c_Source, new P2SourceDelegate);
    delete sd;

    QAbstractItemDelegate* ss = ui->tvSymbols->itemDelegateForColumn(P2SymbolsModel::c_References);
    P2ReferencesDelegate* delegate = new P2ReferencesDelegate;
    connect(delegate, SIGNAL(urlSelected(QUrl)), SLOT(goto_line(QUrl)));
    ui->tvSymbols->setItemDelegateForColumn(P2SymbolsModel::c_References, delegate);
    delete ss;

    ui->tvAsm->setModel(m_amodel);

    P2SymbolSorter* sorter = new P2SymbolSorter(this);
    sorter->setSourceModel(m_smodel);
    ui->tvSymbols->setModel(sorter);
    ui->tvSymbols->setSortingEnabled(true);
}

void MainWindow::setupDisassembler()
{
    ui->tvDasm->setModel(m_dmodel);
    updateDasmColumnSizes();
}

void MainWindow::setupFonts()
{
    static const QString preferred_font = QStringLiteral("Source Code Pro");
    QFont font = QFont(preferred_font);

    if (font.family() != preferred_font)
        font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    font.setStyleHint(QFont::TypeWriter, QFont::PreferAntialias);
    font.setPointSize(9);
    m_font = font;

    font.setPointSize(11);
    ui->tabWidget->setFont(font);

    font.setPointSize(m_asm_font_size);
    ui->tvAsm->setFont(font);
    ui->tvSymbols->setFont(font);
    ui->tbErrors->setFont(font);

    font.setPointSize(m_dasm_font_size);
    ui->tvDasm->setFont(font);
}

void MainWindow::setupTabWidget()
{
    QTabBar* bar = ui->tabWidget->tabBar();
    // FIXME: how to identify tabs if the order changes?
    bar->setTabData(0, id_asm);
    bar->setTabData(1, id_dasm);
    bar->setTabData(2, id_hub);
}

void MainWindow::setupMenu()
{
    connect(ui->action_Open_src, SIGNAL(triggered()), SLOT(openSource()));
    connect(ui->action_Open_src_random, SIGNAL(triggered()), SLOT(loadSourceRandom()));
    // connect(ui->action_Open_obj, SIGNAL(triggered()), SLOT(openObject()));
    connect(ui->action_Open_obj_random, SIGNAL(triggered()), SLOT(loadObjectRandom()));
    connect(ui->action_Go_to_line, SIGNAL(triggered()), SLOT(goto_line_number()));
    connect(ui->action_Assemble, SIGNAL(triggered()), SLOT(assemble()));
    connect(ui->action_SingleStep, SIGNAL(triggered()), SLOT(hubSingleStep()));

    connect(ui->action_Palette_setup, SIGNAL(triggered()), SLOT(palette_setup()));

    connect(ui->action_Asm_Opcodes_bin, SIGNAL(triggered(bool)), SLOT(setAsmOpcodes()));
    connect(ui->action_Asm_Opcodes_byt, SIGNAL(triggered(bool)), SLOT(setAsmOpcodes()));
    connect(ui->action_Asm_Opcodes_dec, SIGNAL(triggered(bool)), SLOT(setAsmOpcodes()));
    connect(ui->action_Asm_Opcodes_hex, SIGNAL(triggered(bool)), SLOT(setAsmOpcodes()));

    connect(ui->action_Asm_DecFontSize, SIGNAL(triggered(bool)), SLOT(decAsmFontSize()));
    connect(ui->action_Asm_IncFontSize, SIGNAL(triggered(bool)), SLOT(incAsmFontSize()));

    connect(ui->action_Dasm_Opcodes_bin, SIGNAL(triggered(bool)), SLOT(setDasmOpcodes()));
    connect(ui->action_Dasm_Opcodes_byt, SIGNAL(triggered(bool)), SLOT(setDasmOpcodes()));
    connect(ui->action_Dasm_Opcodes_dec, SIGNAL(triggered(bool)), SLOT(setDasmOpcodes()));
    connect(ui->action_Dasm_Opcodes_hex, SIGNAL(triggered(bool)), SLOT(setDasmOpcodes()));

    connect(ui->action_Dasm_DecFontSize, SIGNAL(triggered(bool)), SLOT(decDasmFontSize()));
    connect(ui->action_Dasm_IncFontSize, SIGNAL(triggered(bool)), SLOT(incDasmFontSize()));
    connect(ui->action_Dasm_Lowercase, SIGNAL(triggered(bool)), SLOT(setDasmLowercase(bool)));

    connect(ui->action_Go_to_COG, SIGNAL(triggered()), SLOT(goto_cog()));
    connect(ui->action_Go_to_LUT, SIGNAL(triggered()), SLOT(goto_lut()));
    connect(ui->action_Go_to_ROM, SIGNAL(triggered()), SLOT(goto_rom()));
    connect(ui->action_Go_to_address, SIGNAL(triggered()), SLOT(goto_address()));

    // help
    connect(ui->action_Quit, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(ui->action_About, SIGNAL(triggered(bool)), this, SLOT(about()));
    connect(ui->action_AboutQt5, SIGNAL(triggered(bool)), this, SLOT(aboutQt5()));
    connect(ui->action_P2_opcodes, SIGNAL(triggered(bool)), this, SLOT(help_opcodes()));

}

void MainWindow::setupToolbars()
{
    // HUB toolbar
    ui->toolbarHub->addAction(ui->action_SingleStep);

    // Assembler toolbar
    ui->action_Asm_Opcodes_bin->setData(fmt_bin);
    ui->toolbarAsm->addAction(ui->action_Asm_Opcodes_bin);
    ui->action_Asm_Opcodes_byt->setData(fmt_bit);
    ui->toolbarAsm->addAction(ui->action_Asm_Opcodes_byt);
    ui->action_Asm_Opcodes_dec->setData(fmt_dec);
    ui->toolbarAsm->addAction(ui->action_Asm_Opcodes_dec);
    ui->action_Asm_Opcodes_hex->setData(fmt_hex);
    ui->toolbarAsm->addAction(ui->action_Asm_Opcodes_hex);

    ui->toolbarAsm->addSeparator();
    ui->toolbarAsm->addAction(ui->action_Asm_DecFontSize);
    ui->toolbarAsm->addAction(ui->action_Asm_IncFontSize);

    // Expanding spacer
    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->toolbarAsm->addWidget(spacer);

    // Label for count of lines
    QLabel* lbl_lines = new QLabel(tr("%1 lines").arg(0));
    lbl_lines->setObjectName(key_lines);
    lbl_lines->setMinimumWidth(12*10);
    lbl_lines->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lbl_lines->setFrameStyle(QLabel::StyledPanel);
    lbl_lines->setFrameStyle(QLabel::StyledPanel);
    lbl_lines->setFrameShadow(QLabel::Sunken);
    lbl_lines->setBackgroundRole(QPalette::Base);
    ui->toolbarAsm->addWidget(lbl_lines);

    // Disassembler toolbar
    ui->action_Dasm_Opcodes_bin->setData(fmt_bin);
    ui->toolbarDasm->addAction(ui->action_Dasm_Opcodes_bin);
    ui->action_Dasm_Opcodes_byt->setData(fmt_bit);
    ui->toolbarDasm->addAction(ui->action_Dasm_Opcodes_byt);
    ui->action_Dasm_Opcodes_dec->setData(fmt_dec);
    ui->toolbarDasm->addAction(ui->action_Dasm_Opcodes_dec);
    ui->action_Dasm_Opcodes_hex->setData(fmt_hex);
    ui->toolbarDasm->addAction(ui->action_Dasm_Opcodes_hex);

    ui->toolbarDasm->addSeparator();
    ui->toolbarDasm->addAction(ui->action_Go_to_COG);
    ui->toolbarDasm->addAction(ui->action_Go_to_LUT);
    ui->toolbarDasm->addAction(ui->action_Go_to_ROM);
    ui->toolbarDasm->addAction(ui->action_Go_to_address);

    ui->toolbarDasm->addSeparator();
    ui->toolbarDasm->addAction(ui->action_Dasm_Lowercase);

    ui->toolbarDasm->addSeparator();
    ui->toolbarDasm->addAction(ui->action_Dasm_DecFontSize);
    ui->toolbarDasm->addAction(ui->action_Dasm_IncFontSize);

    // Main toolbar
    ui->toolbar->addAction(ui->action_Open_src);
    ui->toolbar->addAction(ui->action_Open_src_random);

    ui->toolbar->addSeparator();
    ui->toolbar->addAction(ui->action_Open_obj);
    ui->toolbar->addAction(ui->action_Open_obj_random);

    ui->toolbar->addSeparator();
    ui->toolbar->addAction(ui->action_Assemble);

    ui->toolbar->addSeparator();
    ui->toolbar->addAction(ui->action_Quit);
}

void MainWindow::setupStatusbar()
{
    QLabel* status = new QLabel(tr("Status"));
    status->setObjectName(key_status);
    ui->statusBar->addWidget(status);
}

void MainWindow::updateAsmColumnSizes()
{
    ui->tvAsm->resizeColumnsToContents();
    ui->tvAsm->resizeRowsToContents();
}

/**
 * @brief Update tvDasm column sizes
 */
void MainWindow::updateDasmColumnSizes()
{
    ui->tvDasm->resizeColumnsToContents();
}

void MainWindow::updateSymbolsColumnSizes()
{
    QFont font = ui->tvSymbols->font();
    QFontMetrics metrics(font);

    QHeaderView* vh = ui->tvSymbols->verticalHeader();
    vh->setEnabled(true);
    vh->setDefaultSectionSize(metrics.ascent() + metrics.descent());

    QHeaderView* hh = ui->tvSymbols->horizontalHeader();
    hh->setContextMenuPolicy(Qt::CustomContextMenu);
    hh->setStretchLastSection(true);
    connect(hh, SIGNAL(customContextMenuRequested(QPoint)), SLOT(setSymbolsHeaderColums(QPoint)), Qt::UniqueConnection);

    for (int i = 0; i < m_smodel->columnCount(); i++) {
        QSize size = m_smodel->sizeHint(static_cast<P2SymbolsModel::column_e>(i));
        ui->tvSymbols->setColumnWidth(i, size.width());
    }
}

void MainWindow::setupCogView()
{
    m_vcog = QVector<P2CogView*>()
             << ui->cog0 << ui->cog1 << ui->cog2 << ui->cog3
             << ui->cog4 << ui->cog5 << ui->cog6 << ui->cog7;
    for (int id = 0; id < 8; id++) {
        P2CogView* vcog = m_vcog[id];
        if (!vcog)
            continue;
        if (id >= ncogs) {
            vcog->hide();
            continue;
        }
        vcog->setCog(m_hub->cog(id));
    }
}
