import QtQuick

// Import "Controls" for Button
import QtQuick.Controls

Rectangle {
    id: page
    width: 400
    height: 400
    color: "white"


        // 3.1 Start/Stop Button
        /*
        The Start button will start an elapsed timer that has a one-second interval in the C++ application. 
        Every time the C++ timer triggers, it increases an integer value that is shown on the QML side. 
        When the timer is running, the button text changes to 'Stop'. 
        If 'Stop' is clicked, the C++ timer is stopped, and the text changes back to 'Start'.
        */

    

    Button {
        id: timerButton
        objectName: "timerButton"
        text: timer.buttonText
        ToolTip.visible: down
        ToolTip.text: qsTr("Start/Stop timer.")
        signal toggleTimer
        onClicked: toggleTimer()
    }

    // 3.2 Readonly Text Field
    /*
    The text field displays the elapsed time of the timer.
    */

    TextField {
        id: timerDisplay
        x: 100
        text: timer.currentTime
        readOnly: true
    }

    // 3.3 List USB Devices Button
    /*
    When clicking this button, the QML UI will display all currently attached USB devices and show their model, vendor, and location.
    Note that this can be platform-specific and must work in your chosen environment as documented in step 5.
    */
    Button {
        y: 50
        id: listUSBButton
        objectName: "listUSBButton"
        text: "List USB Devices"
        ToolTip.visible: down
        ToolTip.text: qsTr("List all usb devices attached.")
        onClicked: usb.listDevices()
    }

    //3.4 Exit Button
    /*
    Clicking this button will cause the C++ application to exit and also shut down the web server.
    */
    Button {
        y: 50
        x: 150
        id: exitButton
        objectName: "exitButton"
        ToolTip.visible: down
        ToolTip.text: qsTr("Close C++ Application and stop Web Server.")
        text: "Exit"
        signal close()
        onClicked: close()
    }

    // 3.5 Cleanup Button
    /*
    Clicking this button will cause the C++ application to exit, shut down, and delete the web server, and also shut down and delete itself.
    Nothing of the C++ application nor the web server must remain on the system.
    */

    Button {
        y: 50
        x: 250
        id: cleanupButton
        objectName: "cleanupButton"
        ToolTip.visible: down
        ToolTip.text: qsTr("Dangerous button that removes all project files!")
        text: "Clean"
        signal clean()
        onClicked: clean()
    }

    // ListView for usb devices
    ListView {
        y: 150
        width: parent.width
        height: 400
        model: usb.deviceList
        delegate: Rectangle {
            width: parent.width
            height: 90
            color: "lightgray"
            border.color: "black"
            border.width: 1
            Column {
                spacing: 5
                padding: 10
                
                Text { text: "Model: " + modelData.Model }
                Text { text: "Vendor: " + modelData.Vendor }
                Text { text: "Location: " + modelData.Location }
                Text {
                    text: "ID: " + modelData.VID + ":" + modelData.PID
                    font.pixelSize: 10
                }
            }
        }
    }

}
