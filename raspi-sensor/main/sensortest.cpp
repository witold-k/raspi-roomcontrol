#include <chrono>
#include <thread>
#include <raspi_sensor>


using namespace std::literals::chrono_literals;
using namespace sensor_data;
using namespace raspi_roomcontrol;


int main(
    int argc,
    const char * argv[]
) {
    (void)argc;
    (void)argv;
    std::cout << "Raspberry Pi DHT11/DHT22 temperature/humidity test"
              << std::endl;;

    DHT_11_22 sensor;
    DHT_11_22::SetupResult sres = sensor.setup();
    if (!sres) {
        std::cerr << sres << std::endl;
        return -1;
    }

    DHT_11_22::Number temp;
    DHT_11_22::Number hum;
    for (;;) {
        sensor.update();
        //temp = temp.forward(sensor.calcTemperature());
        //hum  = hum.forward(sensor.calcHumidity());
        temp = sensor.calcTemperature();
        hum  = sensor.calcHumidity();
        DataSet<8> ds(temp, hum);

        std::cout << ds << std::endl;
        std::this_thread::sleep_for(10s);
    }

    return 0;
}
