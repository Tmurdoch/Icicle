glslc shader.vert -o vert.spv
glslc shader.frag -o frag.spv

Get-Content frag.spv | Set-Content -Encoding utf8 frag.spv
Get-Content vert.spv | Set-Content -Encoding utf8 vert.spv