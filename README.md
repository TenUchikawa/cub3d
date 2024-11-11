


##テスト用
```bash
find maps/good -type f -exec echo -e "\n\n" \; -exec echo {} \; -exec sh -c './cub3d {}' \;
find maps/bad -type f -exec echo -e "\n\n" \; -exec echo {} \; -exec sh -c './cub3d {}' \;

```