set arch i386:x86-64
file trap2

init-if-undefined $run_with_continue = 1

define run-trap
  if $_thread != 0
    kill
  end
  shell killall qemu-x86_64 >/dev/null 2>&1
  shell qemu-x86_64 -g 12948 trap2 < trap2.txt & sleep 0.2
  target remote localhost:12948
  if $run_with_continue != 0
    continue
  end
end

document run-trap
  Run the provided trap executable.
end

define rt
  run-trap
end
