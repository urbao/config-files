return {
    'MeanderingProgrammer/render-markdown.nvim',
    dependencies = { 
        'nvim-treesitter/nvim-treesitter', 
        'nvim-tree/nvim-web-devicons' -- 如果你想要漂亮的小圖標
    },
    ---@module 'render-markdown'
    ---@type render_markdown.Config
    opts = {
        -- 這裡可以進行個人化設定
        heading = {
            -- 標題符號，可以換成你喜歡的樣式
            icons = { '󰲡 ', '󰲣 ', '󰲥 ', '󰲧 ', '󰲩 ', '󰲫 ' },
        },
        code = {
            -- 程式碼區塊的樣式
            style = 'language',
            highlight = 'RenderMarkdownCode',
        },
        checkbox = {
            -- 待辦事項圖標
            unchecked = { icon = '󰄱 ' },
            checked = { icon = '󰄵 ' },
        },
    },
}
