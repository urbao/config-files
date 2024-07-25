return {
    "craftzdog/solarized-osaka.nvim",
    priority = 1000,
    opts = function()
        return {
            transparent = true,
            vim.cmd([[colorscheme solarized-osaka]])
        }
    end,
}
