project('lirium', 'c')

srcfiles = [
    'src/main.c',
    'src/network/network.c',
    'src/network/node.c',
    'src/network/packet.c',
    'src/network/interface.c',
    'src/cli/cli.c',
    'src/cli/lexer.c',
    'src/cli/parser.c'
]


executable(
    'lirium',
    sources: srcfiles,
    include_directories: ['./includes']
)
