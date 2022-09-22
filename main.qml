import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

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
        color: '#2AABEE'
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
                radius: 10
                color: '#229ED9'
                border.color: 'darkblue'
                TextEdit
                {
                    id: textElement
                    anchors.left: rectElement.left
                    anchors.right: rectElement.right
                    anchors.top: rectElement.top
                    anchors.bottom: panelButtons.top
                    font.pointSize: 11
                    textMargin: defMargin
                    wrapMode: TextEdit.Wrap
                    selectByMouse: true
                    text: model.text
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
                        id: clandarButton
                        anchors.top: panelButtons.top
                        anchors.left: panelButtons.left
                        width: 100
                        height: panelButtons.height
                        text: qsTr("Calendar")
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
                        id: progressButton
                        anchors.top: panelButtons.top
                        anchors.right: panelButtons.right
                        width: 100
                        height: panelButtons.height
                        text: qsTr("Progress")
                        leftPadding: 10
                        onClicked:
                        {
                            var str = textElement.text;
                            textElement.text = "";
                            if (progressButton.checked)
                            {
                                textElement.font.strikeout = false;
                                textElement.text = str;
                                console.log("true, " + str)
                                progressButton.checked = false;
                            }
                            else if (!progressButton.checked)
                            {
                                textElement.font.strikeout = true;
                                textElement.text = str;
                                console.log("false, " + str)
                                progressButton.checked = true;
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
        color: "transparent"
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
