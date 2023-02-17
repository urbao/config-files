require("mason").setup()
require("mason-lspconfig").setup({
    ensure_installed = { "arduino_language_server", "clangd", "pyright", "bashls" },
})

-- enable keybinds only for when lsp server available
local on_attach = function(_, _)
  -- keybind options
  local keymap = vim.keymap
  -- set keybinds
  keymap.set("n", "gf", vim.lsp.buf.definition, {}) -- show definition, references
  keymap.set("n", "gd", vim.lsp.buf.implementation, {}) -- see definition and make edits in window
  keymap.set("n", "K", vim.lsp.buf.hover, {})
end



require("lspconfig").arduino_language_server.setup {
    on_attach = on_attach
}

require("lspconfig").bashls.setup {
    on_attach = on_attach
}

require("lspconfig").clangd.setup {
    on_attach = on_attach
}

require("lspconfig").pyright.setup {
    on_attach = on_attach
}

