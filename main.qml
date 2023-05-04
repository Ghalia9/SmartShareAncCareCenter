/*import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

Rectangle {
    id: window

    property double oldLat: 25.6585
    property double oldLng: 100.3658
    property Component comMarker: mapMarker

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
        id: mapView
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(oldLat, oldLng);
        zoomLevel: 6
    }

    function setCenter(lat, lng) {
        mapView.pan(oldLat - lat, oldLng - lng)
        oldLat = lat
        oldLng = lng
    }

    function addMarker(lat, lng) {
        var item = comMarker.createObject(window, {
                                           coordinate: QtPositioning.coordinate(lat, lng)
                                          })
        mapView.addMapItem(item)
    }

    Component {
        id: mapMarker
        MapQuickItem {
            id: markerImg
            anchorPoint.x: image.width/4
            anchorPoint.y: image.height
            coordinate: position

            sourceItem: Image {
                id: image
                source: "http://maps.gstatic.com/mapfiles/ridefinder-images/mm_20_red.png"
            }
        }
    }
}
*/
/*
import QtQuick 2.12
import QtQuick.Window 2.12
import QtLocation 5.12
import QtPositioning 5.12

Window {
    visible: true
    width: 640
    height: 480

    // Create a Map element with the HERE plugin
    Map {
            id: map
            anchors.fill: parent
            plugin: Plugin {
                name: "mapboxgl"
                PluginParameter {
                    name: "mapboxgl.access_token"
                    value: "pk.eyJ1IjoiZ2hhbGlhOSIsImEiOiJjbGdjM3ZtcWcwZGEyM3FxbTM4Y284cGdiIn0.cokvfuuxEZc4r9ftAV901Q"
                }
            }

        // Add a MapQuickItem to the map
        MapQuickItem {
            id: mapPin
            anchorPoint: Qt.point(10, 10)
            coordinate: QtPositioning.coordinate(37.7749, -122.4194)
            sourceItem: Image {
                width: 32
                height: 32
                source: "pin.png"
            }
        }
    }
}
*/
/*
import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6
Rectangle {
    width: 1000
    height: 1000
    Plugin {
        id: mapPlugin
        name: "osm"

        PluginParameter {
            name: "osm.mapping.providersrepository.disabled"
            value: "true"
        }
        PluginParameter {
            name: "osm.mapping.providersrepository.address"
            value: "http://maps-redirect.qt.io/osm/5.6/"
        }
    }

    Map {
        id: mapView
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(36.8988, 10.189710)
        zoomLevel: 11

        MapCircle {
            center {
                latitude: 36.897978
                longitude: 10.190585
            }
            radius: 900.0
            color: 'green'
            border.width: 3
        }

        MapCircle {
            center {
                latitude: 36.896420
                longitude: 10.189983
            }
            radius: 800.0
            color: 'blue'
            border.width: 3
        }

        MapCircle {
            center {
                latitude: 36.900150
                longitude: 10.192920
            }
            radius: 700.0
            color: 'red'
            border.width: 3
        }
    }
}
*/

import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6
import QtQuick.Controls 2.1
import QtQuick.LocalStorage 2.0
import QtQml.Models 2.2

Rectangle {
    id: root
    width: 1000
    height: 1000

    Plugin {
        id: mapPlugin
        name: "osm"

        PluginParameter {
            name: "osm.mapping.providersrepository.disabled"
            value: "true"
        }
        PluginParameter {
            name: "osm.mapping.providersrepository.address"
            value: "http://maps-redirect.qt.io/osm/5.6/"
        }
    }

    Map {
        id: mapView
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(36.8988, 10.189710)
        zoomLevel: 11
        Component.onCompleted: {
                    // Load saved places
                    var db = LocalStorage.openDatabaseSync("mapview", "1.0", "Map view data", 1000000);
                    db.transaction(function(tx) {
                        tx.executeSql('CREATE TABLE IF NOT EXISTS places(lat REAL, lng REAL)');
                        var rs = tx.executeSql('SELECT * FROM places');
                        for (var i = 0; i < rs.rows.length; i++) {
                            var place = Qt.createQmlObject('import QtLocation 5.6; MapCircle {}', mapView);
                            place.center = QtPositioning.coordinate(rs.rows.item(i).lat, rs.rows.item(i).lng);
                            place.radius = 700.0;
                            place.color = 'red';
                            place.border.width = 3;
                            mapView.addMapItem(place);
                        }
                    });
                }
        function addPlace(latitude, longitude) {
                    var place = Qt.createQmlObject('import QtLocation 5.6; MapCircle {}', mapView);
                    place.center = QtPositioning.coordinate(latitude, longitude);
                    place.radius = 700.0;
                    place.color = 'red';
                    place.border.width = 3;
                    mapView.addMapItem(place);

                    // Save the place to the database
                    var db = LocalStorage.openDatabaseSync("mapview", "1.0", "Map view data", 1000000);
                    db.transaction(function(tx) {
                        tx.executeSql('CREATE TABLE IF NOT EXISTS places(lat REAL, lng REAL)');
                        tx.executeSql('INSERT INTO places VALUES(?, ?)', [latitude, longitude]);
                    });
                }
        MapCircle {
            center {
                latitude: 36.897978
                longitude: 10.190585
            }
            radius: 900.0
            color: 'green'
            border.width: 3
        }

        MapCircle {
            center {
                latitude: 36.896420
                longitude: 10.189983
            }
            radius: 800.0
            color: 'blue'
            border.width: 3
        }

        MapCircle {
            center {
                latitude: 36.900150
                longitude: 10.192920
            }
            radius: 700.0
            color: 'red'
            border.width: 3
        }

        Row {
            spacing: 10
            TextField {
                id: latitudeField
                placeholderText: "Latitude"
                width: 110
            }
            TextField {
                id: longitudeField
                placeholderText: "Longitude"
                width: 110
            }
            Button {
                text: "Add Place"
                onClicked: {
                    var latitude = parseFloat(latitudeField.text)
                    var longitude = parseFloat(longitudeField.text)
                    console.log("Latitude: " + latitude)
                    console.log("Longitude: " + longitude)
                    mapView.addPlace(latitude,longitude);
                }
            }
        }
    }
}
