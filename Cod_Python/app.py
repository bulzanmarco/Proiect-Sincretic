from flask import Flask, request, jsonify, render_template
import serial
import time

app = Flask(__name__)

# Configurare pentru portul serial
SERIAL_PORT = 'COM7'  # Asigură-te că acest port este corect
BAUD_RATE = 9600

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/update', methods=['POST'])
def update():
    action = request.form['action']
    response = ''
    try:
        with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=2) as ser:
            if action == 'turn_on':
                ser.write(b'1')
                response = 'APRINS'
            elif action == 'turn_off':
                ser.write(b'0')
                response = 'STINS'
            elif action == 'get_temp_now':
                ser.write(b'r')
                time.sleep(1)  # Așteaptă puțin pentru a asigura transmiterea
                if ser.in_waiting > 0:
                    response = ser.readline().decode('utf-8').strip()
                else:
                    response = 'Eroare la citirea temperaturii'
    except serial.SerialException as e:
        response = f'Eroare la accesarea portului serial: {str(e)}'
    except PermissionError as e:
        response = f'Eroare de permisiune: {str(e)}'
    except Exception as e:
        response = f'Eroare necunoscută: {str(e)}'
    return response

if __name__ == '__main__':
    app.run(debug=True)
