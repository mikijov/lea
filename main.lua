tray = nil
icon = nil
timer = nil
timeout = 0.5

function onNotificationClick(notification)
   lea.log("onNotificationClick")
end

function onItem1()
   lea.log("item1 clicked")
end

function onItem2()
   lea.log("item2 clicked")
end

function onItem3()
   lea.log("item3 clicked")
end

function onItem4()
   lea.log("item4 clicked")
end

function onSubmenu1()
   lea.log("submenu1 clicked")
end

function onSubmenu2()
   lea.log("submenu2 clicked")
end

function onSubmenu3()
   lea.log("submenu3 clicked")
end

function onSubmenu4()
   lea.log("submenu4 clicked")
end

function onMousePress(tray, button, x, y)
   lea.log("onMousePress called " .. button .. ", " .. x .. "x" .. y)

   if button == 1 then
      notification = lea.Notification.create("Cactus", "A notification has been received. Click me if you dare.")
      notification.icon = icon
      notification.onClick = onNotificationClick
      notification:show()
   end
   if button == 3 then
      menu = lea.Menu.create()
      menu:addItem("item 1", onItem1)
      menu:addItem("item 2", onItem2)
      menu:addSeparator()
      menu:addItem("item 3", onItem3)
      menu:addItem("item 4", onItem4)
      submenu = menu:addSubmenu("submenu")
      submenu:addItem("subitem1", onSubmenu1)
      submenu:addItem("subitem2", onSubmenu2)
      submenu:addItem("subitem3", onSubmenu3)
      submenu:addItem("subitem4", onSubmenu4)

      tray:showMenu(menu, button)
   -- else
      -- lea.log("onMouseRelease called " .. button .. ", " .. x .. "x" .. y)
   end
end

function onMouseRelease(tray, button, x, y)
   -- if button == 3 then
   --    menu = lea.Menu.create()
   --    menu:addItem("item 1", nil)
   --    menu:addItem("item 2", nil)
   --    menu:addSeparator()
   --    menu:addItem("item 3", nil)
   --    menu:addItem("item 4", nil)
   --    submenu = menu:addSubmenu("item 1")
   --    submenu:addItem("subitem1", nil)
   --    submenu:addItem("subitem2", nil)
   --    submenu:addItem("subitem3", nil)
   --    submenu:addItem("subitem4", nil)
   --
   --    tray:showMenu(menu, button)
   -- else
      lea.log("onMouseRelease called " .. button .. ", " .. x .. "x" .. y)
   -- end
end

function onMouseScroll(tray, dx, dy)
   lea.log("onMouseScroll called " .. dx .. "x" .. dy)
end

function lea.onConfigure(config)
   lea.log("onConfigure")
   lea.log("Lea version: " .. lea.VERSION)
   config.appName = "xyz.haker.lea.example"
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
