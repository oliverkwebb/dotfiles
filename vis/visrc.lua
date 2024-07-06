require('vis')
require('gofile')
require('tables')

plug = {
  theme = "nvim",
  hilight = require('hilight'),
  spellcheck = require('spellcheck')
}
plug.spellcheck.cmd = "aspell -l %s -a"
plug.spellcheck.list_cmd = "aspell list -l %s -a"
plug.spellcheck.default_lang = "en_US"
plug.hilight.patterns[' +\n']  = { style = 'back:#448844', hideOnInsert = true }
plug.hilight.patterns['TODO']  = { style = 'back:#FF8800' }
plug.hilight.patterns['FIXME'] = { style = 'back:#FF8800' }

vis.events.subscribe(vis.events.FILE_OPEN, function(file)
  if file.name and not os.execute("isbin " .. file.name) then
    io.write("Do you wish to open this? [y/n]? ")
    if io.read(1) ~= "y" then vis:exit(0); end
  end
end)

vis.events.subscribe(vis.events.WIN_OPEN, function(win)
  win.options.numbers = true;
  win.options.relativenumbers = true;
  win.options.expandtab = true;
  win.options.tabwidth = 2;
  vis:command("set theme ".. plug.theme)
  vis:command("set autoindent")
end)
