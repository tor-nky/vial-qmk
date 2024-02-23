#!/bin/sh
version="1_1_2"
make ble_micro_pro:vial:zip -j8
make ble_micro_pro:vial_no_msc:zip -j8
make sekigon/keyboard_quantizer/kqb:no_msc:zip -j8
make sekigon/keyboard_quantizer/mini:vial:uf2 -j8

mkdir .build/release

unzip -o .build/ble_micro_pro_vial.zip -d .build/release
unzip -o .build/ble_micro_pro_vial_no_msc.zip -d .build/release
unzip -o .build/sekigon_keyboard_quantizer_kqb_no_msc.zip -d .build/release

mv .build/release/ble_micro_pro_vial.bin .build/release/ble_micro_pro_vial_${version}.bin
mv .build/release/ble_micro_pro_vial.dat .build/release/ble_micro_pro_vial_${version}.dat
mv .build/release/ble_micro_pro_vial_no_msc.bin .build/release/ble_micro_pro_vial_${version}_no_msc.bin
mv .build/release/ble_micro_pro_vial_no_msc.dat .build/release/ble_micro_pro_vial_${version}_no_msc.dat
mv .build/release/sekigon_keyboard_quantizer_kqb_no_msc.bin .build/release/sekigon_keyboard_quantizer_kqb_${version}_no_msc.bin
mv .build/release/sekigon_keyboard_quantizer_kqb_no_msc.dat .build/release/sekigon_keyboard_quantizer_kqb_${version}_no_msc.dat