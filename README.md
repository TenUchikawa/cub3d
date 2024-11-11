


##テスト用
```bash
find maps/good -type f -exec echo -e "\n\n" \; -exec echo {} \; -exec sh -c './cub3d {}' \;
find maps/bad -type f -exec echo -e "\n\n" \; -exec echo {} \; -exec sh -c './cub3d {}' \;

```


```
── src/
│   ├── main.c
│   ├── init/
│   │   ├── init_config.c
│   │   ├── init_window.c
│   │   ├── init_image.c
│   │   └── load_textures.c
│   ├── parser/
│   │   ├── parser.c
│   │   ├── parser_utils.c
│   │   ├── check_config.c
│   │   └── flood_fill.c
│   ├── raycasting/
│   │   ├── raycasting.c
│   │   ├── draw_column.c
│   │   └── floor_and_ceiling.c
│   ├── player/
│   │   ├── move.c
│   │   └── rotate.c
│   ├── utils/
│   │   ├── get_next_line.c
│   │   └── get_next_line_utils.c
│   └── key_handle.c

```

# 最終ファイル構成は以下にしたい。
# src/init/

## init_config.c
- init_config
- check_cub_extension
- check_xpm_extension

## init_window.c
- init_window

## init_image.c
- init_image
- draw_pixel

## load_textures.c
- load_textures


# src/parser/

## parser.c
- parse_config
- parse_settings_and_map

## parser_utils.c
- parse_color
- parse_texture
- parse_map_line
- replace_end_nl_to_eol
- skip_whitespace

## check_config.c
- check_config
- check_texture_paths
- check_colors
- check_player_start_location
- check_map_chars

## flood_fill.c
- flood_fill
- validate_map
- set_player_location
- is_out_of_bounds
- is_valid_map_char


# src/raycasting/

## raycasting.c
- cast_ray
- calculate_ray
- init_dda
- perform_dda
- determine_texture

## draw_column.c
- draw_column
- draw_wall_column
- init_wall_column
- get_tex_x
- calculate_wall_distance

## floor_and_ceiling.c
- draw_floor_and_ceiling
- draw_ceiling
- draw_floor
- create_color


# src/player/

## move.c
- move_player
- strafe_player

## rotate.c
- rotate_player
- init_dda_x
- init_dda_y


# src/utils/

## get_next_line.c
- get_next_line
- get_to_next_newline
- get_new_line
- get_to_nr

## get_next_line_utils.c
- ft_memcpy
- ft_strchr
- ft_strjoin
- ft_create_s1


# src/

## key_handle.c
- handle_keypress

## main.c
- main
- setup_hooks
- draw_scene