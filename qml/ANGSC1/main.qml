import QtQuick 2.13
import Box2D 2.0
import QtQuick.Particles 2.13
import "Menu"

// Background

Item{
    id: container
    width:950
    height:700

Image {
    id: game
    source:"background-new.png"
    width: container.width
    height: container.height
    fillMode: Image.Tile

    property int screenWidth: width
    property int screenHeight: height

    MainScene{
        id: mainscene
    }

    Component.onCompleted: {
        console.log("start QML")
    }
}
}

