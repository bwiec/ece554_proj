set platform_name [lindex $argv 0]
puts "The platform name is \"$platform_name\""

set ws_path [lindex $argv 1]
puts "The ws path is \"$ws_path\""

set app_name [lindex $argv 2]
puts "The app_name is \"$app_name\""

setws ${ws_path}
platform active ${platform_name}

# Build the applications
app build -name ${app_name}