pragma Singleton

import QtQuick 2.13
import QtQuick.Window 2.13
import QtMultimedia 5.13

QtObject {
    property real textSize:                 10.0
    property real headerTextSize:           18.0
    property real loginControlTextSize:     12.0
    property real loginButtonTextSize:      12.0
    property real settingsTabTextSize:      11.0
    property real settingsButtonTextSize:   11.0

    property color alternateBase:   "#FFDEE6ED"
    property color base:            "#FFE1E1E1"
    property color brightText:      "#FFEDF3F8"
    property color button:          "SteelBlue"
    property color buttonText:      "#FFEDF3F8"
    property color dark:            "#FF91B6D4"
    property color highlight:       "#FF1987E1"
    property color highlightedText: "#FFEDF3F8"
    property color light:           "#FF91B6D4"
    property color link:            "SteelBlue"
    property color linkVisited:     "#FF396A93"
    property color mid:             "#FF2B506E"
    property color midlight:        "#FF6A7F90"
    property color shadow:          "#AA0E1B25"
    property color text:            "#FF29343D"
    property color toolTipBase:     "#AA0E1B25"
    property color toolTipText:     "#FFEDF3F8"
    property color window:          "#FFE1E1E1"
    property color windowText:      "#FFEDF3F8"

    property color accentGreen:     "#FF6BA358"
    property color disabledGreen:   "#FF97A294"
    property color accentRed:       "#FFF24444"
    property color disabledRed:     "#FFFF4380"
    property color headerDropShadow:"#AA4682B4"

    property FontLoader core_font: FontLoader {
        source: "../Resources/fonts/cantarell-bold.otf"
        onStatusChanged: if(core_font.status === FontLoader.Ready) console.log('Loaded Core Font')
    }

    property FontLoader header_font: FontLoader {
        source: "../Resources/fonts/cuppajoe-regular.otf"
        onStatusChanged: if(header_font.status === FontLoader.Ready) console.log('Loaded Header Font')
    }

    property Audio login_music: Audio {
        source: "../Resources/music/menu_loop.ogg"
        audioRole: Audio.GameRole
        autoLoad: true
        autoPlay: true
        loops: Audio.Infinite
        volume: 0.65
    }

    property Audio good_button_sfx: Audio {
        source: "../Resources/sfx/run.ogg"
        audioRole: Audio.SonificationRole
    }

    property Audio bad_button_sfx: Audio {
        source: "../Resources/sfx/zone_border.ogg"
        audioRole: Audio.SonificationRole
    }

    property Audio info_button_sfx: Audio {
        source: "../Resources/sfx/computer.ogg"
        audioRole: Audio.SonificationRole
    }

    Component.onCompleted: {
        console.log("SEGS Theme initialized")
    }
}
