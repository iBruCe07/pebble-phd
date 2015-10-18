module.exports = {

  ajax: function(url, type, callback) {
    var req = new XMLHttpRequest();
    req.onload = function () {
      callback(this.responseText);
    };
    req.open(type, url);
    req.send();
  },

  kelvinToCelsius: function(temp) {
    return Math.round(temp - 273.15);
  }

};