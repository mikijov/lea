# Lea

Lua powered simple app engine.

## Features
- system tray icon
- notification
- svg icons


```lua

lea.onConfigure(conf)
lea.onInit()
lea.onQuit()

lea.quit()
lea.log(msg)

lea.loadIcon(filename)
lea.createTrayIcon(icon)
lea.createTimer(timeoutSeconds, shouldRepeat)
lea.createMenu()
lea.createNotification(title, message, icon)

tray.onMousePress
tray.onMouseRelease
tray.onMouseScroll
tray:show()
tray:hide()

timer.onTick
timer:stop()
timer:resetTimeout(timeoutSeconds, shouldRepeat)

menu:addItem(label, callback, userdata)
menu:addSeparator()
menu:addSubMenu(label)

notification.onClick
notification.setTimeout(nf, seconds)

```
