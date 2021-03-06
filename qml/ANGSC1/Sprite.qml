import QtQuick 2.13

Item{
    id:sprite
    clip: true
    property alias running: timer.running;
    property int frame:0
    property int frameCount: 0;
    property alias source:image.source

    Image{
         id:image
         x:-sprite.width*sprite.frame
     }

    Timer {
        id:timer
        interval: 200; running: false; repeat: true
        onTriggered: {
            nextFrame();
        }
    }

    function prevFrame() {
        sprite.frame = --sprite.frame  % sprite.frameCount
    }

    function nextFrame() {
        sprite.frame = ++sprite.frame  % sprite.frameCount
    }
}
