import serial
import pyowm


owm = pyowm.OWM('b70f1eb9ecaf7b8d7969efbd141de9bf')
observation = owm.weather_at_place('Los Angeles')
w = observation.get_weather()

def getTempCelsius(data = w):
    q = data.get_temperature('celsius')
    currentT = round(q['temp'], 2)
    highT = round(q['temp_max'], 2)
    lowT = round(q['temp_min'], 2)
    weatherString = "It is " + str(currentT) + " degrees Celsius, with a high of " + str(highT) + " and a low of " + str(lowT)
    return weatherString

def getTempFahrenheit(data = w):
    q = data.get_temperature('fahrenheit')
    currentT = round(q['temp'], 2)
    highT = round(q['temp_max'], 2)
    lowT = round(q['temp_min'], 2)
    weatherString = "It is " + str(currentT) + " degrees Fahrenheit with a high of " + str(highT) + " and a low of " + str(lowT)
    return weatherString

def getWind(data = w):
    q = data.get_wind()
    windSpeed = round(q['speed'], 2)
    windString = "There is a " + str(windSpeed) + " m/s wind today"
    return windString


#possibly not needed
def sendWeather(ser, weatherInfo):
    ser.write((str(len(weatherInfo) / 2) + " ").encode('utf-8'))
    ser.write(weatherInfo.encode('utf-8'))
    mes = ser.readline()
    while not mes:
        mes = ser.readline()
    print(mes)

    
if __name__ == '__main__':
    comm_port = "COM5"
    sampleInput = serial.Serial(comm_port, 115200, timeout=5)
    while(not sampleInput.read()):
        pass
    # sampleInput.write("1".encode('utf-8'));
    sendWeather(sampleInput, getTempFahrenheit(w))
    
