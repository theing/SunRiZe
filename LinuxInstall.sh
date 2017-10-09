#!/bin/bash

echo "I will install SunRiZe in /opt/SunRiZe"

if [ ! `id -u` == 0 ]
then
  echo "This script needs to be run by root"
  exit 1
fi

if [ ! -d "bin" ]
then
  echo "This script must be launched by the SunRiZe folder"
  exit 1
fi

echo -n "Proceed ? (N/y) "
read answ
echo $answ

if [ "$answ" == "Y" ] || [ "$answ" == "y" ]
then
  echo "Installing ..."
  mkdir -p /opt/SunRiZe
  install -m 644 bin/* /opt/SunRiZe
  chmod 755 /opt/SunRiZe/SunRiZe
  cat << EOF >/usr/share/applications/SunRiZe.desktop
[Desktop Entry]
Name=SunRiZe
GenericName=MCUs MDD
Exec=/opt/SunRiZe/SunRiZe
Type=Application
Keywords=MDD;Tools;
Terminal=False
Icon=/opt/SunRiZe/SunRiZe.png
Categories=Development;Tools;
EOF
fi 

echo "Done !"
