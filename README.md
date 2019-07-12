# The "BounceStudio API" PHP 7 extension
## Topline
This extension is a PHP API of the BounceStudio library of the BoogieTools, Inc. The extension utilizes functions of that library and completely depends on it.
That library enables your application to recognize thousands of email bounce formats. Easy to use, robust, extremely fast, and accurate, BounceStudio API was designed for professional Linux developers who demand the best.

## Installation
1. Make a temporary folder:
```bash
mkdir /tmp/bouncestudio_install
cd /tmp/bouncestudio_install
```
2. Download and extract the most recent BounceStudio library:
```bash
wget https://www.boogietools.com/download/Linux/BounceStudioAPI/BounceStudioAPI-linux.tar.gz
tar -xvzf BounceStudioAPI-linux.tar.gz
```
3. Place the BounceStudio lib into a proper place on your machine (we will build it on the x86_64 platform so we use appropriate lib file and system folder):
```bash
sudo cp BounceStudioAPI-linux/libBounceStudio64.so.3.7.0.962 /usr/lib64/
sudo ln -s /usr/lib64/libBounceStudio64.so.3.7.0.962 /usr/lib64/libBounceStudio64.so
```
4. Time to checkout this repo:
```bash
git clone git clone ssh://git@git.avaaz.org:7999/developers/bouncestudio-php-7.git
```
5. Copy `BounceStudio.h` to the folder of the extension you want to build (we will build the extension for the PHP7. For PHP5 use appropriate folder):
```bash
cp BounceStudioAPI-linux/BounceStudio.h bouncestudio-php-7/
```
6. Now we are ready do build it. So let's do it:
```bash
cd bouncestudio-php-7/
phpize
./configure --enable-bouncestudio
make CFLAGS="-lBounceStudio64 $CFLAGS"
```
7. Install the extension lib to the php modules folder:
```bash
sudo make install
```
8. Do not forget to enable the extension in your `php.ini` configuration with:
```ini
extension=bouncestudio.so
```
9. Let's check it's enabled:
```bash
php --ri "BounceStudio API"
```
