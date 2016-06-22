#ifndef LOGGING_H
#define LOGGING_H

#include <QObject>
#include <QTextStream>
#include <QDateTime>
#include <QFile>

class Logging : public QObject
{
    Q_OBJECT
public:
    explicit Logging(QString filename = 0, QObject *parent = 0);
    ~Logging();

public slots:
    void write(QString message);

signals:
    void log(QString);

private:
    QTextStream out;
    QFile file;
    QDateTime dt;
};

#endif // LOGGING_H
