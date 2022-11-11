currDir=$(echo $(pwd))

libName="TGUI"
libVersion="0.9.5"

if [ -d "/usr/local/include/TGUI" ]; then
    echo "TGUI Already installed.\nAborting."
    exit 0
fi


dirName="./tmp"
zipFile="$libName.zip"
zipPath="$currDir/$dirName/$zipFile"

dirCreated=1
hasDL=1
isInst=1

mkdir -p "$dirName" && cd "$dirName"

dirCreated=$?

if [ $dirCreated -eq 0 ]; then
    echo "$dirName folder created. Navigating inside."
    echo "Downloading $libName v$libVersion..."
    wget https://github.com/texus/TGUI/archive/v$libVersion.zip -O $zipFile && unzip "$zipPath" -d .
    hasDownloaded=$?
else
    echo "\033[0;31mFailed to create the installation folder.\nAborting.\033[0m"
fi


if [ $hasDownloaded -eq 0 ]; then
    echo "Downloaded."
    echo "Installing it..."
    cd "$libName-$libVersion" && cmake . && sudo make install
    isInst=$?
else
    echo "\033[0;31mFailed to download the source code.\nAborting.\033[0m"
fi

if [ $isInst -eq 0 ]; then
    echo "\033[0;32m$libName Successfully installed.\033[0m"
else
    echo "\033[0;31mFailed to install TGUI\033[0m"
fi

if [ $dirCreated -eq 0 ]; then
    cd "$currDir" && rm -rf "$dirName"
fi