import QtQuick 2.15
import QtQuick.Window 2.12

Window {
    visible: true
    width: 1280
    height: 720
    title: qsTr("Hello World")

    ChangeDatabase {
        width: 100
        height: 100
    }
}
