## How to build

#### Quick installation by using a script ####

```ruby
curl -fsSL https://raw.githubusercontent.com/D3SXX/QT/refs/heads/main/quick_setup.sh | bash
```

#### Manual installation ####

1. Clone the repository:

```ruby
git clone https://github.com/D3SXX/QT.git
```

2. Install dependencies

```ruby
sudo apt update
sudo apt install git nodejs npm qt6-base-dev-tools qt6-base-dev-tools libusb-1.0-0-dev qt6-declarative-dev qml6-module-qtquick qml6-module-qtquick-controls
qml6-module-qtqml-workerscript qml6-module-qtquick-templates cmake pkg-config --yes
```

3. Build QT APP

```ruby
cd QT_APP
cmake .
cmake --build .

mv appQT_APP ../APP
```

4. Build Web Server

```ruby
cd web-server
npm install
```
Done!

## Usage ##

1. Start the Web Server

```ruby
cd web-server
npm run start
```
2. Start the APP

Either launch the executable from the UI or from console

```ruby
    ./APP
```  