#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>

class Timer : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString currentTime READ getTime NOTIFY timeChanged)  // Connect text field to timeChanged signal
    Q_PROPERTY(QString buttonText READ getButtonText NOTIFY buttonTextChanged) // Connect button to time buttonTExtChanged signal
    
public:
    Timer() {
        connect(timer, &QTimer::timeout, this, &Timer::updateTime); // Every time times changes it calls updateTime
    }

public slots:
    void toggleTimer();
    
    QString getTime();
    QString getButtonText();

signals:
    void timeChanged();
    void buttonTextChanged();

private slots:
    void updateTime();

private:
    QTimer *timer = new QTimer(); // timer will be used to call updateTime every 1 sec.
    QString m_currentTime = "00:00:00";
    QString m_buttonText = "Start";
    int m_seconds = 0;
};

#endif // TIMER_H
