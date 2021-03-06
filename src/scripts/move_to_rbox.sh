#!/bin/bash

# Moves the account of the given user to the rbox mail format
#
# Parameter $1 user id
# Parameter $2 destination path  
#
user="$1"
dest_path="$2"

# Load utility script
script_path=${0%/*}
source "$script_path/utils.sh"
source "$script_path/doveadm.sh"

# Read mail_location of user
mail_location=$(get_user_mail_location "$user")

# Synchronize from mdbox to rbox
result=$(doveadm_backup "$dest_path" "$user" rbox)
[ "$result" -eq 0 ] || { echo "doveadm sync failed"; exit 1; }
result=$(doveadm_backup "$dest_path" "$user" rbox)
[ "$result" -eq 0 ] || { echo "doveadm sync failed"; exit 1; }

# Copy files from mdbox to rbox
copy_files "$mail_location" "$dest_path" "$user" 
echo $?
