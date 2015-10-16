var utils = require('../../../src/js/utils.js');
var app = require('../../../src/js/app.js');

describe("app", function() {

  beforeEach(function() {
    spyOn(utils, 'ajax').and.callFake(function(url, method, fn) {
      fn(fixtures.openWeatherMapResponse);
    });

    spyOn(navigator.geolocation, 'getCurrentPosition').and.callFake(function(success, error, options) {
      success({ coords: { latitude: 0, longitude: 0 } });
    });
  });

  it("should be defined", function() {
    expect(app).toBeDefined();

    expect(Pebble.events.ready).toBeDefined();
    expect(Pebble.events.appmessage).toBeDefined();
  });

  it("should send weather data given a ready event", function() {
    spyOn(Pebble, 'sendAppMessage');

    Pebble.events.ready();

    expect(Pebble.sendAppMessage).toHaveBeenCalledWith({
        'KEY_TEMPERATURE': 10,
        'KEY_CONDITIONS': "Clouds"
      }, jasmine.any(Function), jasmine.any(Function));
  });

  it("should send weather data given an appmessage event", function() {
    spyOn(Pebble, 'sendAppMessage');

    Pebble.events.appmessage();

    expect(Pebble.sendAppMessage).toHaveBeenCalledWith({
        'KEY_TEMPERATURE': 10,
        'KEY_CONDITIONS': "Clouds"
      }, jasmine.any(Function), jasmine.any(Function));
  });

});
