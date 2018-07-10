#!/bin/bash
# HJV : 1.0 Wrapper build script for easy building saves lots of headache for others i.e setup thingy sdk bla blah...
#

UNDER='\e[4m'
RED='\e[31;1m'
GREEN='\e[32;1m'
YELLOW='\e[33;1m'
BLUE='\e[34;1m'
MAGENTA='\e[35;1m'
CYAN='\e[36;1m'
WHITE='\e[37;1m'
ENDCOLOR='\e[0m'

PROJECT_ROOT=`pwd`
export SDK_PATH="${PROJECT_ROOT}/Nordic-Thingy52-FW"
export NRF_UTILS_INSTALL="${PROJECT_ROOT}/pc-nrfutil"
export NRF_UTILS_BIN_PATH="${PROJECT_ROOT}/bin"
export PATH=$PATH:${PROJECT_ROOT}/toolchain/gcc-arm-none-eabi-4_9-2015q3/bin/:${NRF_UTILS_BIN_PATH}
export BOOTLOADER_KEY="${PROJECT_ROOT}/keys/private-key.pem"
export APP_PATH="${SDK_PATH}/project/pca20020_s132/armgcc"
export BL_PATH="${SDK_PATH}/project/bootloader_secure/pca20020/armgcc"
export DFU_PATH="${PROJECT_ROOT}/DFU"
export EMAIL="brennanho@shaw.ca"

function generate_sfu_key_and_cfile()
{
	nrfutil keys generate private-key.pem
}

function clean_thingy_52_app()
{
	echo -e "$RED Cleaning Application $ENDCOLOR"
	cd ${SDK_PATH}/project/pca20020_s132/armgcc
	make -j8 clean
}

function build_thingy_52_app()
{
	echo  -e "$CYAN Building Application $ENDCOLOR"
	cd ${SDK_PATH}/project/pca20020_s132/armgcc
	make -j8
}

function clean_thingy_52_bl()
{
	echo -e "$RED Cleaning Bootloader $ENDCOLOR"
	cd ${SDK_PATH}/project/bootloader_secure/pca20020/armgcc
	make -j8 clean
}

function build_thingy_52_bl()
{
	echo -e "$CYAN Building Bootloader $ENDCOLOR"
	cd ${SDK_PATH}/project/bootloader_secure/pca20020/armgcc
	make -j8
}

function generate_thingy_52_bl_keyarray()
{
	nrfutil keys display --key pk --format code ${BOOTLOADER_KEY} --out_file dfu_public_key.c
}

function generate_dfu()
{
	echo -e "$BLUE Buidling DFU with Application Only $ENDCOLOR"
	nrfutil pkg generate --application ${APP_PATH}/_build/nrf52832_xxaa_s132.hex  --application-version 1 --hw-version 52 --sd-req 0x98 --key-file ${BOOTLOADER_KEY} ${DFU_PATH}/dfu-app.zip
}

function email_dfu()
{
	echo -e "$BLUE Sending DFU Package to ${EMAIL} $ENDCOLOR"
	echo  -e "Thingy DFU:`date +%Y_%m_%d-%H_%M_%S` \nEmail Contains zip File:dfu-app.zip\nRegards,\nThingy52 Server" | mailx -s "Thingy DFU Package Built on `date +%Y_%m_%d-%H_%M_%S`" -r bluemagicserver@shaw.ca -A ${DFU_PATH}/dfu-app.zip ${EMAIL}
}

#build_thingy_52_app
#build_thingy_52_bl
#generate_dfu
#email_dfu

function clean_rule()
{
	echo -e "$RED Clean request $1 $ENDCOLOR"
	case "$1" in
		bootloader)
			clean_thingy_52_bl
			;;
		application)
			clean_thingy_52_app
			;;
		all)
			clean_thingy_52_bl
			clean_thingy_52_app
			rm -rf ${PROJECT_ROOT}/DFU/*
			;;
		*)
			echo "Invalid clean argument"
			;;
	esac
}

function build_rule()
{
	echo -e "$CYAN Build request $1 $ENDCOLOR"
	case "$1" in
		bootloader)
			build_thingy_52_bl
			;;
		application)
			build_thingy_52_app
			;;
		dfu)
			generate_dfu
			email_dfu
			;;
		all)
			build_thingy_52_bl
			build_thingy_52_app
			generate_dfu
			email_dfu
			;;
		*)
			echo "Invalid build argument"
			;;
	esac
}

while getopts 'cbeh:' OPTION; do
  case "$OPTION" in
    c)
      echo -e "$RED Cleaning... $OPTARG $ENDCOLOR"
	x=$2
	clean_rule $2
      ;;

    b)
      echo -e "$GREEN Building... $OPTARG $ENDCOLOR"
	x=$2
	build_rule $2
      ;;
    e)
      echo -e "$BLUE Emailing... $OPTARG $ENDCOLOR"
	generate_dfu
	email_dfu
      ;;
    h)
      echo "script usage: $(basename $0) [-c all, bootloader, application, dfu] [-b all, bootloader, application, dfu]" >&2
      exit 1
      ;;

    ?)
      echo "script usage: $(basename $0) [-c all, bootloader, application, dfu] [-b all, bootloader, application, dfu]" >&2
      exit 1
      ;;
  esac
done
shift "$(($OPTIND -1))"
