# zeemo 

zeemo is a midi to cv expander. 

it outputs voltages between -10 and +10 volts. using the default uf2, it has ~14 bits of resolution (~0.02 volts). the pwm output filtering seems to have only [~0.01 volt rms](https://www.falstad.com/circuit/circuitjs.html?ctz=CQAgjCAMB0l3BWEBmAHAJmgdgGzoRmACzICcpkORICkNIJNApgLRhgBQASiC8unTCl0vfoJx1JDOmxFSYCDgCdRA8MNV18OKCHQDIHZNQBeANwD2AGwAuAQwDmTADoBHMFLDZiyBOlRC-pCoIcisWLoiHlAcJpp6CDp8amJ6IObW9k5uHhwO8anJdMjIOpIcAO7x2rzoWCI1hlVFKGosdSKphgDGtfWtMh0JZeDhIKTQpAi0CGgIuB64ULCQnAIR7f017ejUNdRmSkwAZmyGduBEe1uJev2k4CKy4PDwvDCvBKiQRKj8qEQEKQPIkkIJXoZ8sQ9rdoXoiPJlJdqCUdDVUZEIZVhncGrcMU1kXoQkSCdi4f5UOAwA0SYYVOxaVT+MSqcVkPByTTWdTOqUYgzuRiWQS9Fj1q0UPy2DoMQcjqdcgB5HFDSm43SGHgsUhoklsK48rSXN5eHBIM1g5boTgqHV6qksX5Gl5wDi9J1U9WesVs5avfjkIPBkNlaA4er6IHGGmQRI4MNwTjNZ0CKlgNHBGJQzPptEIzXYn3qlnqwwWcBUqi6AAeNOOHJECGgIQzVCw8wjRDAQP9Sd0nCAA) when overclocking the pwm of the pico.


## circuitpython

1. download the [latest circuitpython uf2](https://circuitpython.org/board/raspberry_pi_pico/). install by drag and drop.
2. download the [latest circuitpython libraries](https://github.com/adafruit/Adafruit_CircuitPython_Bundle/releases/tag/20230424). install the `adafruit_midi` folder by drag and drop.