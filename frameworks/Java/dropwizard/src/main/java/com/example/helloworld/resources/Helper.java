package com.example.helloworld.resources;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Optional;
import java.util.Set;
import java.util.concurrent.ThreadLocalRandom;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

/**
 * Provides utility methods for the benchmark tests. Taken from undertow-edge
 * project with additions.
 */
public final class Helper {
	private static final int[] ids;

	static {
		List<Integer> temp = IntStream.rangeClosed(1, 10000).boxed().collect(Collectors.toList());
		Collections.shuffle(temp);
		ids = temp.stream().mapToInt(x -> x).toArray();
	}

	private Helper() {
		throw new AssertionError();
	}

	static int getQueries(Optional<String> queries) {
		if (!queries.isPresent()) {
			return 1;
		}
		return getQueries(queries.get());
	}

	static int getQueries(String queries) {
		try {
			int parsedValue = Integer.parseInt(queries);
			return Math.min(500, Math.max(1, parsedValue));
		} catch (NumberFormatException e) {
			return 1;
		}
	}

	public static int randomWorld() {
		return 1 + ThreadLocalRandom.current().nextInt(10000);
	}

	public static int[] randomWorlds(int count) {
		int[] result = new int[count];
		int start = ThreadLocalRandom.current().nextInt(10000);
		for (int i = 0; i < count; i++) {
			result[i] = ids[(start + i) % ids.length];
		}
		return result;
	}

	public static void main(String[] args) {
		int[] x = randomWorlds(20000);
		System.out.println(Arrays.toString(x));
		System.out.println(x.length);
		Set<Integer> set = Arrays.stream(x).boxed().collect(Collectors.toSet());
		System.out.println(set.size());
	}
}