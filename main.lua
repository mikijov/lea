tray = nil
icon = nil
timer = nil
timeout = 0.5

function onNotificationClick(notification)
   lea.log("onNotificationClick")
end

function onMousePress(tray, button, x, y)
   lea.log("onMousePress called " .. button .. ", " .. x .. "x" .. y)

   if button == 1 then
      notification = lea.Notification.create("Cactus", "A notification has been received. Click me if you dare.")
      notification.icon = icon
      notification.onClick = onNotificationClick
      notification:show()
   end
end

function onMouseRelease(tray, button, x, y)
   if button == 3 then
      lea.quit()
   else
      lea.log("onMouseRelease called " .. button .. ", " .. x .. "x" .. y)
   end
end

function onMouseScroll(tray, dx, dy)
   lea.log("onMouseScroll called " .. dx .. "x" .. dy)
end

function lea.onConfigure()
   lea.log("onConfigure")
end

function onTimeout1(self)
   lea.log("timer1")

   timer = lea.Timer.create(1, true)
   timer.onTimeout = onTimeout2
end

function onTimeout2(self)
   timeout = timeout * 2
   if timeout > 50 then
      lea.log("Stopping timer.")
      self:stop()
      timer = nil
   else
      lea.log("Will wait " .. timeout .. " seconds.")
      self:reset(timeout, true)
   end
end

function lea.onInit()
   lea.log("onInit")

   icon = lea.Icon.load("../cactus.svg")
   tray = lea.SystemTray.create(icon)
   tray.onMousePress = onMousePress
   tray.onMouseRelease = onMouseRelease
   tray.onMouseScroll = onMouseScroll

   timer = lea.Timer.create(1, false)
   timer.onTimeout = onTimeout1
end

function lea.onQuit()
   lea.log("onQuit")
end
