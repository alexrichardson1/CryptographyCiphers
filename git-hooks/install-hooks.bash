#!/usr/bin/env bash

# Run the command `chmod +x ./install-hooks.bash` in the scripts directory

HOOK_DIR=git-hooks
GIT_DIR=$(git rev-parse --git-dir)

chmod +x commit-msg.py pre-push.bash

echo "Installing hooks..."
# symlinks to the pre-commit script
ln -sf $GIT_DIR/../$HOOK_DIR/commit-msg.py $GIT_DIR/hooks/commit-msg
ln -sf $GIT_DIR/../$HOOK_DIR/pre-push.bash $GIT_DIR/hooks/pre-push
echo "Done!"
