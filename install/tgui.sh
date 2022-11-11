mkdir tmp && cd tmp
wget https://github.com/texus/TGUI/archive/v0.9.5.zip
tar -xf TGUI-0.9.5.zip

cd TGUI-0.9.5
cmake .
sudo make install
cd ../..
rm -r tmp