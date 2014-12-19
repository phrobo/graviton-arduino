Graviton for Arduino
####################

This is an implementation of `Graviton <http://graviton.phrobo.net/>`_ for the
Arduino platform.

Usage
-----

In your Arduino sketch:

.. code::

  #include <XBee.h>
  #include <Graviton.h>

  XBee bee;
  GravitonXBeeReader reader (&bee);

  GravitonMethod methods[] = {
    { "ping", do_ping },
  };

  GravitonService services[] = {
    {
      "com.example.ping",
      1,
      methods
    },
    Graviton::introspectionService
  };

  Graviton graviton (&reader, services, 2);

  void setup() {
  }

  void loop()
  {
    graviton.loop();
  }

  void serialEvent() {
    reader.serialEvent();
  }
