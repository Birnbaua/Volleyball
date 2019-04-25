/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../planer/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[67];
    char stringdata0[1530];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "updateWorker"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 15), // "Worker::dataUi*"
QT_MOC_LITERAL(4, 41, 3), // "log"
QT_MOC_LITERAL(5, 45, 18), // "messageBoxCritical"
QT_MOC_LITERAL(6, 64, 3), // "msg"
QT_MOC_LITERAL(7, 68, 21), // "messageBoxInformation"
QT_MOC_LITERAL(8, 90, 17), // "messageBoxWarning"
QT_MOC_LITERAL(9, 108, 15), // "userCheckButton"
QT_MOC_LITERAL(10, 124, 4), // "head"
QT_MOC_LITERAL(11, 129, 12), // "updateUiData"
QT_MOC_LITERAL(12, 142, 4), // "data"
QT_MOC_LITERAL(13, 147, 16), // "updateWorkerData"
QT_MOC_LITERAL(14, 164, 26), // "on_actionBeenden_triggered"
QT_MOC_LITERAL(15, 191, 24), // "on_actionAbout_triggered"
QT_MOC_LITERAL(16, 216, 30), // "on_actionShowlogfile_triggered"
QT_MOC_LITERAL(17, 247, 20), // "updateTournamentTime"
QT_MOC_LITERAL(18, 268, 18), // "fieldsValueChanged"
QT_MOC_LITERAL(19, 287, 35), // "on_spinBoxAnzahlfelder_valueC..."
QT_MOC_LITERAL(20, 323, 4), // "arg1"
QT_MOC_LITERAL(21, 328, 31), // "on_pushButtonConfigSave_clicked"
QT_MOC_LITERAL(22, 360, 35), // "on_pushButtonConfigRollback_c..."
QT_MOC_LITERAL(23, 396, 32), // "on_pushButtonConfigReset_clicked"
QT_MOC_LITERAL(24, 429, 30), // "on_pushButtonSaveTeams_clicked"
QT_MOC_LITERAL(25, 460, 31), // "on_pushButtonResetTeams_clicked"
QT_MOC_LITERAL(26, 492, 31), // "on_pushButtonPrintTeams_clicked"
QT_MOC_LITERAL(27, 524, 17), // "teamsValueChanged"
QT_MOC_LITERAL(28, 542, 31), // "on_pushButtonVrGenerate_clicked"
QT_MOC_LITERAL(29, 574, 28), // "on_pushButtonVrClear_clicked"
QT_MOC_LITERAL(30, 603, 27), // "on_pushButtonVrSave_clicked"
QT_MOC_LITERAL(31, 631, 34), // "on_pushButtonVrChangeGames_cl..."
QT_MOC_LITERAL(32, 666, 28), // "on_pushButtonVrPrint_clicked"
QT_MOC_LITERAL(33, 695, 29), // "on_pushButtonVrResult_clicked"
QT_MOC_LITERAL(34, 725, 15), // "copyVrTableView"
QT_MOC_LITERAL(35, 741, 16), // "pasteVrTableView"
QT_MOC_LITERAL(36, 758, 14), // "vrValueChanged"
QT_MOC_LITERAL(37, 773, 24), // "vrValueChangedFinishEdit"
QT_MOC_LITERAL(38, 798, 33), // "on_pushButtonVrAllResults_cli..."
QT_MOC_LITERAL(39, 832, 31), // "on_pushButtonZwGenerate_clicked"
QT_MOC_LITERAL(40, 864, 27), // "on_pushButtonZwSave_clicked"
QT_MOC_LITERAL(41, 892, 28), // "on_pushButtonZwClear_clicked"
QT_MOC_LITERAL(42, 921, 34), // "on_pushButtonZwChangeGames_cl..."
QT_MOC_LITERAL(43, 956, 28), // "on_pushButtonZwPrint_clicked"
QT_MOC_LITERAL(44, 985, 29), // "on_pushButtonZwResult_clicked"
QT_MOC_LITERAL(45, 1015, 15), // "copyZwTableView"
QT_MOC_LITERAL(46, 1031, 16), // "pasteZwTableView"
QT_MOC_LITERAL(47, 1048, 14), // "zwValueChanged"
QT_MOC_LITERAL(48, 1063, 24), // "zwValueChangedFinishEdit"
QT_MOC_LITERAL(49, 1088, 31), // "on_pushButtonKrGenerate_clicked"
QT_MOC_LITERAL(50, 1120, 27), // "on_pushButtonKrSave_clicked"
QT_MOC_LITERAL(51, 1148, 28), // "on_pushButtonKrClear_clicked"
QT_MOC_LITERAL(52, 1177, 28), // "on_pushButtonKrPrint_clicked"
QT_MOC_LITERAL(53, 1206, 15), // "copyKrTableView"
QT_MOC_LITERAL(54, 1222, 16), // "pasteKrTableView"
QT_MOC_LITERAL(55, 1239, 14), // "krValueChanged"
QT_MOC_LITERAL(56, 1254, 24), // "krValueChangedFinishEdit"
QT_MOC_LITERAL(57, 1279, 31), // "on_pushButtonPlGenerate_clicked"
QT_MOC_LITERAL(58, 1311, 27), // "on_pushButtonPlSave_clicked"
QT_MOC_LITERAL(59, 1339, 28), // "on_pushButtonPlClear_clicked"
QT_MOC_LITERAL(60, 1368, 28), // "on_pushButtonPlPrint_clicked"
QT_MOC_LITERAL(61, 1397, 29), // "on_pushButtonPlResult_clicked"
QT_MOC_LITERAL(62, 1427, 15), // "copyPlTableView"
QT_MOC_LITERAL(63, 1443, 16), // "pastePLTableView"
QT_MOC_LITERAL(64, 1460, 14), // "plValueChanged"
QT_MOC_LITERAL(65, 1475, 24), // "plValueChangedFinishEdit"
QT_MOC_LITERAL(66, 1500, 29) // "on_checkBoxBettysPlan_clicked"

    },
    "MainWindow\0updateWorker\0\0Worker::dataUi*\0"
    "log\0messageBoxCritical\0msg\0"
    "messageBoxInformation\0messageBoxWarning\0"
    "userCheckButton\0head\0updateUiData\0"
    "data\0updateWorkerData\0on_actionBeenden_triggered\0"
    "on_actionAbout_triggered\0"
    "on_actionShowlogfile_triggered\0"
    "updateTournamentTime\0fieldsValueChanged\0"
    "on_spinBoxAnzahlfelder_valueChanged\0"
    "arg1\0on_pushButtonConfigSave_clicked\0"
    "on_pushButtonConfigRollback_clicked\0"
    "on_pushButtonConfigReset_clicked\0"
    "on_pushButtonSaveTeams_clicked\0"
    "on_pushButtonResetTeams_clicked\0"
    "on_pushButtonPrintTeams_clicked\0"
    "teamsValueChanged\0on_pushButtonVrGenerate_clicked\0"
    "on_pushButtonVrClear_clicked\0"
    "on_pushButtonVrSave_clicked\0"
    "on_pushButtonVrChangeGames_clicked\0"
    "on_pushButtonVrPrint_clicked\0"
    "on_pushButtonVrResult_clicked\0"
    "copyVrTableView\0pasteVrTableView\0"
    "vrValueChanged\0vrValueChangedFinishEdit\0"
    "on_pushButtonVrAllResults_clicked\0"
    "on_pushButtonZwGenerate_clicked\0"
    "on_pushButtonZwSave_clicked\0"
    "on_pushButtonZwClear_clicked\0"
    "on_pushButtonZwChangeGames_clicked\0"
    "on_pushButtonZwPrint_clicked\0"
    "on_pushButtonZwResult_clicked\0"
    "copyZwTableView\0pasteZwTableView\0"
    "zwValueChanged\0zwValueChangedFinishEdit\0"
    "on_pushButtonKrGenerate_clicked\0"
    "on_pushButtonKrSave_clicked\0"
    "on_pushButtonKrClear_clicked\0"
    "on_pushButtonKrPrint_clicked\0"
    "copyKrTableView\0pasteKrTableView\0"
    "krValueChanged\0krValueChangedFinishEdit\0"
    "on_pushButtonPlGenerate_clicked\0"
    "on_pushButtonPlSave_clicked\0"
    "on_pushButtonPlClear_clicked\0"
    "on_pushButtonPlPrint_clicked\0"
    "on_pushButtonPlResult_clicked\0"
    "copyPlTableView\0pastePLTableView\0"
    "plValueChanged\0plValueChangedFinishEdit\0"
    "on_checkBoxBettysPlan_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      60,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  314,    2, 0x06 /* Public */,
       4,    1,  317,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,  320,    2, 0x08 /* Private */,
       7,    1,  323,    2, 0x08 /* Private */,
       8,    1,  326,    2, 0x08 /* Private */,
       9,    2,  329,    2, 0x08 /* Private */,
      11,    1,  334,    2, 0x08 /* Private */,
      13,    0,  337,    2, 0x08 /* Private */,
      14,    0,  338,    2, 0x08 /* Private */,
      15,    0,  339,    2, 0x08 /* Private */,
      16,    0,  340,    2, 0x08 /* Private */,
      17,    0,  341,    2, 0x08 /* Private */,
      18,    0,  342,    2, 0x08 /* Private */,
      19,    1,  343,    2, 0x08 /* Private */,
      21,    0,  346,    2, 0x08 /* Private */,
      22,    0,  347,    2, 0x08 /* Private */,
      23,    0,  348,    2, 0x08 /* Private */,
      24,    0,  349,    2, 0x08 /* Private */,
      25,    0,  350,    2, 0x08 /* Private */,
      26,    0,  351,    2, 0x08 /* Private */,
      27,    0,  352,    2, 0x08 /* Private */,
      28,    0,  353,    2, 0x08 /* Private */,
      29,    0,  354,    2, 0x08 /* Private */,
      30,    0,  355,    2, 0x08 /* Private */,
      31,    0,  356,    2, 0x08 /* Private */,
      32,    0,  357,    2, 0x08 /* Private */,
      33,    0,  358,    2, 0x08 /* Private */,
      34,    0,  359,    2, 0x08 /* Private */,
      35,    0,  360,    2, 0x08 /* Private */,
      36,    0,  361,    2, 0x08 /* Private */,
      37,    0,  362,    2, 0x08 /* Private */,
      38,    0,  363,    2, 0x08 /* Private */,
      39,    0,  364,    2, 0x08 /* Private */,
      40,    0,  365,    2, 0x08 /* Private */,
      41,    0,  366,    2, 0x08 /* Private */,
      42,    0,  367,    2, 0x08 /* Private */,
      43,    0,  368,    2, 0x08 /* Private */,
      44,    0,  369,    2, 0x08 /* Private */,
      45,    0,  370,    2, 0x08 /* Private */,
      46,    0,  371,    2, 0x08 /* Private */,
      47,    0,  372,    2, 0x08 /* Private */,
      48,    0,  373,    2, 0x08 /* Private */,
      49,    0,  374,    2, 0x08 /* Private */,
      50,    0,  375,    2, 0x08 /* Private */,
      51,    0,  376,    2, 0x08 /* Private */,
      52,    0,  377,    2, 0x08 /* Private */,
      53,    0,  378,    2, 0x08 /* Private */,
      54,    0,  379,    2, 0x08 /* Private */,
      55,    0,  380,    2, 0x08 /* Private */,
      56,    0,  381,    2, 0x08 /* Private */,
      57,    0,  382,    2, 0x08 /* Private */,
      58,    0,  383,    2, 0x08 /* Private */,
      59,    0,  384,    2, 0x08 /* Private */,
      60,    0,  385,    2, 0x08 /* Private */,
      61,    0,  386,    2, 0x08 /* Private */,
      62,    0,  387,    2, 0x08 /* Private */,
      63,    0,  388,    2, 0x08 /* Private */,
      64,    0,  389,    2, 0x08 /* Private */,
      65,    0,  390,    2, 0x08 /* Private */,
      66,    0,  391,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,    6,   10,
    QMetaType::Void, 0x80000000 | 3,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateWorker((*reinterpret_cast< Worker::dataUi*(*)>(_a[1]))); break;
        case 1: _t->log((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->messageBoxCritical((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->messageBoxInformation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->messageBoxWarning((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: { bool _r = _t->userCheckButton((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->updateUiData((*reinterpret_cast< Worker::dataUi*(*)>(_a[1]))); break;
        case 7: _t->updateWorkerData(); break;
        case 8: _t->on_actionBeenden_triggered(); break;
        case 9: _t->on_actionAbout_triggered(); break;
        case 10: _t->on_actionShowlogfile_triggered(); break;
        case 11: _t->updateTournamentTime(); break;
        case 12: _t->fieldsValueChanged(); break;
        case 13: _t->on_spinBoxAnzahlfelder_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_pushButtonConfigSave_clicked(); break;
        case 15: _t->on_pushButtonConfigRollback_clicked(); break;
        case 16: _t->on_pushButtonConfigReset_clicked(); break;
        case 17: _t->on_pushButtonSaveTeams_clicked(); break;
        case 18: _t->on_pushButtonResetTeams_clicked(); break;
        case 19: _t->on_pushButtonPrintTeams_clicked(); break;
        case 20: _t->teamsValueChanged(); break;
        case 21: _t->on_pushButtonVrGenerate_clicked(); break;
        case 22: _t->on_pushButtonVrClear_clicked(); break;
        case 23: _t->on_pushButtonVrSave_clicked(); break;
        case 24: _t->on_pushButtonVrChangeGames_clicked(); break;
        case 25: _t->on_pushButtonVrPrint_clicked(); break;
        case 26: _t->on_pushButtonVrResult_clicked(); break;
        case 27: _t->copyVrTableView(); break;
        case 28: _t->pasteVrTableView(); break;
        case 29: _t->vrValueChanged(); break;
        case 30: _t->vrValueChangedFinishEdit(); break;
        case 31: _t->on_pushButtonVrAllResults_clicked(); break;
        case 32: _t->on_pushButtonZwGenerate_clicked(); break;
        case 33: _t->on_pushButtonZwSave_clicked(); break;
        case 34: _t->on_pushButtonZwClear_clicked(); break;
        case 35: _t->on_pushButtonZwChangeGames_clicked(); break;
        case 36: _t->on_pushButtonZwPrint_clicked(); break;
        case 37: _t->on_pushButtonZwResult_clicked(); break;
        case 38: _t->copyZwTableView(); break;
        case 39: _t->pasteZwTableView(); break;
        case 40: _t->zwValueChanged(); break;
        case 41: _t->zwValueChangedFinishEdit(); break;
        case 42: _t->on_pushButtonKrGenerate_clicked(); break;
        case 43: _t->on_pushButtonKrSave_clicked(); break;
        case 44: _t->on_pushButtonKrClear_clicked(); break;
        case 45: _t->on_pushButtonKrPrint_clicked(); break;
        case 46: _t->copyKrTableView(); break;
        case 47: _t->pasteKrTableView(); break;
        case 48: _t->krValueChanged(); break;
        case 49: _t->krValueChangedFinishEdit(); break;
        case 50: _t->on_pushButtonPlGenerate_clicked(); break;
        case 51: _t->on_pushButtonPlSave_clicked(); break;
        case 52: _t->on_pushButtonPlClear_clicked(); break;
        case 53: _t->on_pushButtonPlPrint_clicked(); break;
        case 54: _t->on_pushButtonPlResult_clicked(); break;
        case 55: _t->copyPlTableView(); break;
        case 56: _t->pastePLTableView(); break;
        case 57: _t->plValueChanged(); break;
        case 58: _t->plValueChangedFinishEdit(); break;
        case 59: _t->on_checkBoxBettysPlan_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(Worker::dataUi * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::updateWorker)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::log)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 60)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 60;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 60)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 60;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::updateWorker(Worker::dataUi * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::log(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
