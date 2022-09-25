import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Window {
    id: root
    width: 400
    height: 650
    visible: true
    title: qsTr("Organizer")
    readonly property int defMargin: 10
    Rectangle
    {
        id: rectList
        anchors.left: root.left
        anchors.top: root.top
        width: root.width
        height: root.height - rectText.height
        color: '#daad86'//'#2AABEE'
        border.color: 'darkblue'
        ListView
        {
            id: listTasks
            anchors.top: rectList.top
            anchors.bottom: rectList.bottom
            anchors.left: rectList.left
            anchors.right: rectList.right
            anchors.margins: defMargin / 2
            spacing: defMargin
            ScrollBar.vertical: ScrollBar{}
            model: listModel1

            delegate: Rectangle
            {
                id: rectElement
                width: listTasks.width
                height: 100
                radius: defMargin
                color: '#bc986a'
                border.color: '#8d8741'
                Flickable
                {
                    id: flick2
                    width: rectElement.width
                    height: rectElement.height / 2
                    contentWidth: textElement.paintedWidth
                    contentHeight: textElement.paintedHeight
                    clip: true
                    function ensureVisible(r)
                    {
                        if (contentX >= r.x)
                            contentX = r.x;
                        else if (contentX+width <= r.x+r.width)
                            contentX = r.x+r.width-width;
                        if (contentY >= r.y)
                            contentY = r.y;
                        else if (contentY+height <= r.y+r.height)
                            contentY = r.y+r.height-height;
                    }
                    TextEdit
                    {
                        id: textElement
                        width: flick2.width
                        height: flick2.height
                        font.pointSize: 11
                        textMargin: defMargin
                        wrapMode: TextEdit.Wrap
                        selectByMouse: true
                        text: model.text
                        onCursorRectangleChanged: flick2.ensureVisible(cursorRectangle)
                    }
                }
                Rectangle
                {
                    id: panelButtons
                    anchors.left: rectElement.left
                    anchors.bottom: rectElement.bottom
                    anchors.margins: defMargin / 2
                    width: rectElement.width - defMargin
                    height: 40
                    color: rectElement.color
                    Button
                    {
                        id: calendarButton
                        anchors.top: panelButtons.top
                        anchors.left: panelButtons.left
                        width: 100
                        height: panelButtons.height
                        text: qsTr("Select a date")
                        Calendar
                        {
                            id: popUpCalendar
                            anchors.top: calendarButton.bottom
                            width: 250
                            height: popUpCalendar.width
                            visible: false
                            Button
                            {
                                id: acceptDeadLine
                                anchors.top: popUpCalendar.bottom
                                anchors.right: popUpCalendar.right
                                text: qsTr("Accept")
                                onClicked:
                                {
                                    calendarButton.text = Qt.formatDate(popUpCalendar.selectedDate, "dd.MM.yyyy")
                                    popUpCalendar.visible = false
                                }
                            }
                        }
                        onClicked:
                        {
                            if (popUpCalendar.visible == true)
                            {
                                popUpCalendar.visible = false
                            }
                            else
                            {
                                popUpCalendar.visible = true
                            }
                        }
                    }
                    Button
                    {
                        id: deleteButton
                        anchors.bottom: panelButtons.bottom
                        anchors.centerIn: panelButtons
                        width: 100
                        height: panelButtons.height
                        text: qsTr("Delete")
                        onClicked:
                        {
                            listModel1.remove(index)
                        }
                    }
                    Button
                    {
                        property bool check: false
                        id: progressButton
                        anchors.top: panelButtons.top
                        anchors.right: panelButtons.right
                        width: 100
                        height: panelButtons.height
                        text: qsTr("Complite")
                        leftPadding: 10
                        icon.source: "ok.png"
                        onClicked:
                        {
                            var str = textElement.text;
                            textElement.text = "";
                            if (check === false)
                            {
                                textElement.font.strikeout = true;
                                textElement.text = str;
                                check = true;
                                progressButton.checked = true;
                            } else if (check === true)
                            {
                                textElement.font.strikeout = false;
                                textElement.text = str;
                                check = false;
                                progressButton.checked = false
                            }
                        }
                    }
                }
            }
        }
    }

    ListModel
    {
        id:listModel1
        ListElement
        {
            text: qsTr("Complite a homework")
        }

        ListElement
        {
            text: qsTr("Go to the store")
        }
    }

    Rectangle
    {
        id: rectText
        anchors.top: rectList.bottom
        anchors.left: root.left
        width: root.width - addButton.width
        height: 50
        color: "white"
        border.color: 'black'
        Flickable
        {
            id: flick
            width: rectText.width
            height: rectText.height
            contentWidth: textTask.paintedWidth
            contentHeight: textTask.paintedHeight
            clip: true
            function ensureVisible(r)
            {
                if (contentX >= r.x)
                    contentX = r.x;
                else if (contentX+width <= r.x+r.width)
                    contentX = r.x+r.width-width;
                if (contentY >= r.y)
                    contentY = r.y;
                else if (contentY+height <= r.y+r.height)
                    contentY = r.y+r.height-height;
            }
            TextEdit
            {
                id: textTask
                width: flick.width
                height: flick.height
                z: 1
                focus: true
                font.pointSize: 11
                text: ""
                wrapMode: TextEdit.Wrap
                selectByMouse: true
                topPadding: rectText.height / 3
                leftPadding: defMargin
                onCursorRectangleChanged: flick.ensureVisible(cursorRectangle)
            }
        }
        Button
        {
            id: addButton
            anchors.left: rectText.right
            text: qsTr("Add")
            height: rectText.height
            onClicked:
            {
                listModel1.append({text: textTask.text})
                textTask.text = ""
            }
        }
    }
}

