sudo apt update
sudo apt install git nodejs npm qt6-base-dev-tools qt6-base-dev-tools libusb-1.0-0-dev qt6-declarative-dev
if [ -d ./QT ]
    then
        echo "Found QT, skipping git clone"
    else
        git clone https://github.com/D3SXX/QT.git
fi
	
cd QT

cd web-server
npm install

cd ..

cd QT_APP
cmake .
cmake --build .

mv appQT_APP ../APP

echo "Done!"
