#pragma once

#include <string>

namespace ProjectWork2 {

    class SensorData {

        public:
            SensorData(void);
            SensorData(double temperature, int motion, double humidity);

        public:
            double get_temperature(void) const;
            double get_humidity(void) const;
            int get_motion(void) const;

            void set_temperature(double temperature);
            void set_humidity(double humidity);
            void set_motion(int motion);

        public:
            std::string to_string(void) const;
            std::string to_json(void) const;

        private:
            double temperature;
            double humidity;
            int motion;
    };

};
