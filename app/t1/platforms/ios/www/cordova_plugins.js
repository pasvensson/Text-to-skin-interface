cordova.define('cordova/plugin_list', function(require, exports, module) {
module.exports = [
    {
        "file": "plugins/cordova-plugin-rfduino/www/rfduino.js",
        "id": "cordova-plugin-rfduino.rfduino",
        "pluginId": "cordova-plugin-rfduino",
        "clobbers": [
            "rfduino"
        ]
    }
];
module.exports.metadata = 
// TOP OF METADATA
{
    "cordova-plugin-rfduino": "0.1.4",
    "cordova-plugin-whitelist": "1.2.1"
}
// BOTTOM OF METADATA
});