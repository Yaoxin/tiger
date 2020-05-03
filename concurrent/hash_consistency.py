#!/usr/bin/env python
# -*- coding: utf-8 -*-

# 一致性hash算法

from zlib import crc32
import memcache


class HashConsistency(object):
    def __init__(self, nodes=None, replicas=5):
        self.nodes_map = []
        self.nodes_replicas = {}
        self.nodes = nodes
        self.replicas = replicas

        if self.nodes:
            for node in self.nodes:
                self._add_nodes_map(node)
            self._sort_nodes()

    def get_node(self, key):
        key_hash = abs(crc32(key))
        for node in self.nodes_map:
            if key_hash > node[0]:
                continue
            return node
        return None

    def add_node(self, node):
        self._add_nodes_map(node)
        self._sort_nodes()

    def remove_node(self, node):
        if node not in self.nodes_replicas.keys():
            return

        discard_rep_nodes = self.nodes_replicas[node]
        self.nodes_map = filter(lambda x: x[0] not in discard_rep_nodes, self.nodes_map)

    def _add_nodes_map(self, node):
        node_reps = []
        for i in range(self.replicas):
            rep_node = '{}_{}'.format(node, i)
            node_hash = abs(crc32(rep_node))
            self.nodes_map.append((node_hash, node))
            node_reps.append(node_hash)

        self.nodes_replicas[node] = node_reps

    def _sort_nodes(self):
        self.nodes_map = sorted(self.nodes_map, key=lambda x: x[0])


if __name__ == '__main__':
    memcache_servers = [
        '127.0.0.1:7001',
        '127.0.0.1:7002',
        '127.0.0.1:7003',
        '127.0.0.1:7004'
    ]

    h = HashConsistency(memcache_servers)

    mc_servers_dict = {}
    for ms in memcache_servers:
        mc = memcache.Client([ms], debug=True)

    for i in range(10):
        key = 'key_%s'.format(i)
        server = h.get_node(key)[1]
        mc = mc_servers_dict[server]
        mc.set(key, i)
        print('SERVER: %s '.format(server))
