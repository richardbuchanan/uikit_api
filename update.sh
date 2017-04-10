#!/bin/bash

basedir=`pwd`

# Determine the update mode.
git=true
for dir in sources/*
do
  if ! [ -d "$basedir/$dir/.git" ]
  then
    git=false
    break
  fi
done

# Update libraries.
if [ $git == true ]
then
  echo -e "# Rebuilding UIkit API reference sources via GIT"
  for dir in sources/*
  do
    cd $basedir/$dir
    echo -en "$dir\n"
    git pull
  done
  cd $basedir
fi

# Re-index UIkit API reference sources.
for dir in ../../sites/*
do
  if [ -f "$basedir/$dir/settings.php" ]
  then
    cd $basedir/$dir
    install_profile=`drush vget install_profile`
    if echo "$install_profile" | grep -q uikit_api
    then
      # Re-index UIkit API reference sources with Drush queue runner.
      echo -e "# Updating UIkit API reference"
      count=`drush queue-list | grep 'api_parse' | sed -e 's/[^0-9]//g'`
      if [ $count -eq 0 ]
      then
        echo -en "Initializing update\r"
        drush cron -q 2> /dev/null
        count=`drush queue-list | grep 'api_parse' | sed -e 's/[^0-9]//g'`
      fi
      while [ $count -gt 0 ]
      do
        echo -en "$count items remaining   \r"
        drush queue-run api_parse -q 2> /dev/null
        count=`drush queue-list | grep 'api_parse' | sed -e 's/[^0-9]//g'`
      done
    fi
  fi
done
cd $basedir