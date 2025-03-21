#include "timer.h"

#include "QDebug"


// Toggler for timer
// Toggles based on the IsActive() prop of QTimer
void Timer::toggleTimer() {
    if (timer->isActive()) {
        timer->stop();
        m_buttonText = "Start";
        emit buttonTextChanged();
    } else {
        timer->start(1000); // 1 sec.
        m_buttonText = "Stop";
        emit buttonTextChanged();
    }
}

void Timer::updateTime() {
    m_seconds++; // increment value

    // Interesting way of making a time string for the QLM text field
    m_currentTime = QString("%1:%2:%3")
                        .arg(m_seconds / 3600, 2, 10, QChar('0'))
                        .arg((m_seconds % 3600) / 60, 2, 10, QChar('0'))
                        .arg(m_seconds % 60, 2, 10, QChar('0'));
    emit timeChanged();
}

QString Timer::getTime() {
    return m_currentTime;
}

QString Timer::getButtonText(){
    return m_buttonText;
}
