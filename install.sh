printf "\nUpdate to latest hrev..."
pkgman fu

printf "\nChecking out source tree..."
cd ~/Projects/haiku
git pull

printf "\nBuilding driver..."
cd ~/Projects/haiku/src/add-ons/kernel/drivers/audio/es137x
jam -q

printf "\nInstalling driver...\n"
cp -v /boot/home/Projects/haiku/generated/objects/haiku/x86_64/release/add-ons/kernel/drivers/audio/es137x/es137x_audio /boot/home/config/non-packaged/add-ons/kernel/drivers/bin/

printf "\nDone!"

