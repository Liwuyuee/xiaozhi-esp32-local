#!/bin/bash

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

print_error() {
    echo -e "${RED}Error: $1${NC}" >&2
}

print_success() {
    echo -e "${GREEN}Success: $1${NC}"
}

print_info() {
    echo -e "${YELLOW}Info: $1${NC}"
}

check_dist_directory() {
    if [ ! -d "dist" ]; then
        print_error "\`dist\` directory does not exist"
        exit 1
    fi
    
    if [ ! "$(ls -A dist)" ]; then
        print_error "\`dist\` directory is empty"
        exit 1
    fi
}

check_compression_tools() {
if command -v gzip >/dev/null 2>&1; then
        print_success "gzip found, will use gzip to compress"
    else
        print_error "gzip is not found"
        exit 1
    fi
}

prepare_gzipped_directory() {
    if [ -d "gzipped" ]; then
        print_info "clearing existing \`gzipped\` directory"
        rm -rf gzipped/*
    else
        print_info "creating \`gzipped\` directory..."
        mkdir -p gzipped
    fi
}

setup_reproducible_env() {
    export SOURCE_DATE_EPOCH=1
    export TZ=UTC
}

compress_file() {
    local src_file="$1"
    local dst_file="$2"

    mkdir -p "$(dirname "$dst_file")"
    
    gzip -n -c "$src_file" > "$dst_file"
}

compress_dist_files() {
    local file_count=0

    while IFS= read -r -d '' file; do
        rel_path="${file#dist/}"

        dst_file="gzipped/${rel_path}.gz"
        
        print_info "Compressing: $file -> $dst_file"
        compress_file "$file" "$dst_file"
        
        file_count=$((file_count + 1))
    done < <(find dist -type f -print0)
    
    print_success "Compression completed, processed $file_count files"
}

main() {
    check_dist_directory
    check_compression_tools
    prepare_gzipped_directory
    setup_reproducible_env
    compress_dist_files
    
    print_success "All operations completed, compressed files are saved to \`gzipped\` directory"
}

main "$@" 