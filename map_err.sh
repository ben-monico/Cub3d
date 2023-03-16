#! /bin/sh
make re
mkdir vg_out
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --log-file=vg_out/valgrind-out1.txt ./cub3d maps/err/.cub
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --log-file=vg_out/valgrind-out2.txt ./cub3d maps/err/errext_cub
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --log-file=vg_out/valgrind-out3.txt ./cub3d maps/err/noext
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --log-file=vg_out/valgrind-out4.txt ./cub3d maps/err/void.cub
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --log-file=vg_out/valgrind-out5.txt ./cub3d maps/err/dupkeys.cub
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --log-file=vg_out/valgrind-out6.txt ./cub3d maps/err/misskeys.cub
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --log-file=vg_out/valgrind-out7.txt ./cub3d maps/err/wrongkeys.cub